using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.SignalR;
using Microsoft.EntityFrameworkCore;
using MinimalAPIPostgresSqlCSS.Data;
using MinimalAPIPostgresSqlCSS.Models;
using static MinimalAPIPostgresSqlCSS.Crypt;
using System.Net;
using System.Runtime.CompilerServices;
using System.Security.Cryptography;
using System.Text;
using System.Text.Json.Serialization;
using System.Web.Http.Results;
using MinimalAPIPostgresSqlCSS;
using Microsoft.AspNetCore.Mvc;


/*
 * This class is the app builder of the app,
 * where is created the host of the api, 
 * and all the routes for http/https request.
 * 
 * @author David G. Ortiz Velez
 * 
 */

var MyAllowSpecificOrigins = "_myAllowSpecificOrigins";
var builder = WebApplication.CreateBuilder(args);

 /* This Cross-Origin Resource Sharing services 
 * allows any origin with any header or method
 * to request from outside of the domain.
 */
builder.Services.AddCors(options =>
{
    options.AddPolicy(name: MyAllowSpecificOrigins,
                      policy =>
                      {
                          policy.WithOrigins("http://localhost:3000", "https://chamaecrista-ui.azurewebsites.net/")
                                                  .AllowAnyHeader()
                                                  .AllowAnyMethod();
                      });
});

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();
//Initializando conexion
var connectionString = builder.Configuration.GetConnectionString("PostgreSQLConnection");
//Agregates a postgresql server with the dependencies
builder.Services.AddDbContext<CSSDb>(options =>
options.UseNpgsql(connectionString));


var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

//app.UseHttpsRedirection()
app.UseCors(MyAllowSpecificOrigins);







// Admin post request that send a new admins object to the data base.
app.MapPost("/Admins/", async (Admins a, CSSDb db) =>
{
    if (a.Admin_Password == null) return Results.NoContent();

    a.Admin_Password = Crypt.Encrypt(a.Admin_Password);
    db.Admins.Add(a);
    await db.SaveChangesAsync();

    return Results.Created($"/Admins/{a.User_Id}", a);
});

//Admin get request that will get an admin by id.
app.MapGet("/Admins/{id:int}", async (int id, CSSDb db) =>
{
    return await db.Admins.FindAsync(id)
    is Admins a
    ? Results.Ok(a)
    : Results.NotFound();

});
//This route verify if the key and the password are correct.
app.MapPost("/Admins/Auth",  (Admins a, CSSDb db) =>
{
    var privatekey = "DD2CCB091346B250C927F3FD5BB1AD1872078CFE8F572A7324DA2A0981FE2E6B";

    if(privatekey != a.Admin_Email || a.Admin_Password == null) return Results.Unauthorized();

    var pas = db.Admins.OrderBy(x => x.User_Id).Last().Admin_Password;

    if (pas != null)
    {
        if (Crypt.Decrypt(pas) == a.Admin_Password)
        {
            return Results.Ok(db.Admins.OrderBy(x => x.User_Id).LastOrDefault());
        }
    }

    return Results.NotFound();

});

    //Admin get all, will get all admins into a list.
    app.MapGet("/AdminsAll",  (CSSDb db) =>  db.Admins.ToListAsync());

    //Admin put will update an existing value by id. 
    app.MapPut("/Admins/{id:int}", async (int id, Admins a, CSSDb db) =>
    {
        if (a.User_Id != id) return Results.BadRequest();

        var admins = await db.Admins.FindAsync(id);

        if (admins is null) return Results.NotFound();

        admins.User_Id = a.User_Id;
        admins.Admin_Email = a.Admin_Email;
        admins.Admin_Password = a.Admin_Password;

        await db.SaveChangesAsync();
        return Results.Ok(admins);
    });

    //Delete an existing admin by id.
    app.MapDelete("/Admins/{id:int}", async (int id, CSSDb db) =>
    {
        var admins = await db.Admins.FindAsync(id);

        if (admins is null) return Results.NotFound();

        db.Admins.Remove(admins);
        await db.SaveChangesAsync();

        return Results.NoContent();
    });

    //Get command by admin id.
    app.MapGet("/Admins/Commands/{id:int}", (int id, CSSDb db) =>
    {
        var properties = (from Commands in db.Commands.Where(st => st.AdminsUser_Id == id).DefaultIfEmpty()
                          select new
                          {
                              AdminsUser_Id = (int?)Commands.AdminsUser_Id,
                              Command_Id = (int?)Commands.Command_Id,
                              Command_String = (string?)Commands.Command_String
                          }); 

        IResult result = Results.Ok(properties) == null ? Results.NotFound() :  Results.Ok(properties);

        return result;

    });

    //Post Commands send new commands object to database.
    app.MapPost("/Commands/", async (Commands a, CSSDb db) =>
    {
        var properties = (
                        from Commands1 in db.Commands.DefaultIfEmpty()
                        select new
                        {
                            Command_Id = (int?)Commands1.Command_Id,
                            Command_Read = Commands1.Command_Read,
                            Command_String = Commands1.Command_String,
                            Command_Value = Commands1.Command_Value,
                            Command_Performed=Commands1.Command_Performed,
                            Log_Id = Commands1.Log_Id,
                            Log_Text = Commands1.Logs.Timestamps
                        }).Where(b => b.Command_String == a.Command_String && b.Command_Performed == null && b.Command_Value == a.Command_Value).OrderBy(x => x.Command_Id).FirstOrDefault();

        if (properties == null)
        {
            db.Commands.Add(a);
            db.SaveChanges();
            return Results.Created($"/Commands/{a.Command_Id}", a);
        }
        else
        {
            var commands = await db.Commands.FindAsync(properties.Command_Id);
            var Logs = await db.Logs.FindAsync(properties.Log_Id);

            if (commands is null) return Results.NotFound();
            if (Logs is null) return Results.NotFound();
          
            Logs.Timestamps = a.Logs.Timestamps;
            commands.Command_Received = a.Command_Received;
            db.SaveChanges();

            return Results.Ok(commands);
        }
    });

    //Get command by id if not reply not found.
    app.MapGet("/Commands/{id:int}", async (int id, CSSDb db) =>
    {
        return await db.Commands.FindAsync(id)
        is Commands a
        ? Results.Ok(a)
        : Results.NotFound();

    });

    //Get all commands from database
    app.MapGet("/CommandsAll",  (CSSDb db) =>
    {
        var properties = (
                           from Commands in db.Commands
                           select new
                           {
                               Command_Id = (int?)Commands.Command_Id,
                               Command_Read = Commands.Command_Read,
                               Command_Performed = Commands.Command_Performed,
                               Command_String = Commands.Command_String,
                               Command_Value = Commands.Command_Value,
                               Command_Received = Commands.Command_Received,
                               Duplicate_Flag = Commands.Duplicate_Flag,
                               Log_Id = Commands.Log_Id,
                               AdminsUser_Id = Commands.AdminsUser_Id

                           }).OrderByDescending(b => b.Command_Id).ToList().DefaultIfEmpty();
        if (properties == null) return Results.NoContent();
        return Results.Ok(properties);

    });


    //Update a command if the command exist.
    app.MapPut("/Commands/{id:int}", async (int id, Commands a, CSSDb db) =>
    {

        if (a.Command_Id != id) return Results.BadRequest();

        var Commands = await db.Commands.FindAsync(id);

        if (Commands is null) return Results.NotFound();

        Commands.Command_Id = a.Command_Id;
        Commands.Command_String = a.Command_String;
        Commands.Command_Value = a.Command_Value;
        Commands.Command_Received = a.Command_Received;
        Commands.Command_Performed = a.Command_Performed;
        Commands.Command_Read = a.Command_Read;
        Commands.Duplicate_Flag = a.Duplicate_Flag;
        Commands.AdminsUser_Id = a.AdminsUser_Id;
        Commands.Log_Id = a.Log_Id;

        await db.SaveChangesAsync();

        return Results.Ok(Commands);



    });

    //Update a command if the commands_read column by id exist if not reply not found.
    app.MapPut("/Commands/Command_Read", async (Commands a, CSSDb db) =>
    {
        var properties = (
                          from Commands1 in db.Commands.DefaultIfEmpty()
                             select new
                             {
                                 Command_Id = (int?)Commands1.Command_Id,
                                 Command_Read = Commands1.Command_Read,
                                 Command_Performed = Commands1.Command_Performed,
                                 Command_String = Commands1.Command_String,
                                 Command_Value = Commands1.Command_Value
                             }).Where(b => b.Command_Performed == null && b.Command_String != "RetrainModel").OrderBy(x => x.Command_Id).FirstOrDefault();

        if (properties == null) return Results.NoContent();

        var Commands = await db.Commands.FindAsync(properties.Command_Id);

        if (Commands is null) return Results.NotFound();

        Commands.Command_Read = a.Command_Read;


        await db.SaveChangesAsync();

        properties = (
                             from Commands1 in db.Commands.DefaultIfEmpty()
                             select new
                             {
                                 Command_Id = (int?)Commands1.Command_Id,
                                 Command_Read = Commands1.Command_Read,
                                 Command_Performed = Commands1.Command_Performed,
                                 Command_String = Commands1.Command_String,
                                 Command_Value = Commands1.Command_Value
                             }).Where(b => b.Command_Performed == null && b.Command_String != "RetrainModel").OrderBy(x => x.Command_Id).FirstOrDefault();

        return Results.Ok(properties);
    });

    //This route send the last retrainmodel Command that is in the queue.
    app.MapPut("/Commands/RetrainModel/Command_Read", async (Commands a, CSSDb db) =>
    {
        var properties = (
                      from Commands1 in db.Commands.DefaultIfEmpty()
                      select new
                      {
                          Command_Id = (int?)Commands1.Command_Id,
                          Command_Read = Commands1.Command_Read,
                          Command_Performed = Commands1.Command_Performed,
                          Command_String = Commands1.Command_String
                      }).Where(b => b.Command_Performed == null && b.Command_String == "RetrainModel").OrderBy(x => x.Command_Id).FirstOrDefault();

        if (properties == null) return Results.NoContent();

        var Commands = await db.Commands.FindAsync(properties.Command_Id);

        if (Commands is null) return Results.NotFound();

        Commands.Command_Read = a.Command_Read;

        await db.SaveChangesAsync();

        properties = (
                         from Commands1 in db.Commands.DefaultIfEmpty()
                         select new
                         {
                             Command_Id = (int?)Commands1.Command_Id,
                             Command_Read = Commands1.Command_Read,
                             Command_Performed = Commands1.Command_Performed,
                             Command_String = Commands1.Command_String

                         }).Where(b => b.Command_Performed == null && b.Command_String == "RetrainModel").OrderBy(x => x.Command_Id).FirstOrDefault();

        return Results.Ok(properties);

    });
//Update a command if the commands_performed column by id exist if not reply not found.
    app.MapPut("/Commands/Command_Performed", async (Commands a, CSSDb db) =>
    {
        var properties = (
                               from Commands1 in db.Commands.DefaultIfEmpty()
                               select new
                               {
                                   Command_Id = (int?)Commands1.Command_Id,
                                   Command_Performed = Commands1.Command_Performed,
                                   Command_String=Commands1.Command_String,
                                   Commands1.Command_Read,
                                   Log_Id = Commands1.Log_Id,
                                   Log_Text = Commands1.Logs.Log_Text

                               }).Where(b => b.Command_Performed == null&& b.Command_Read!=null && b.Command_String != "RetrainModel").OrderBy(x => x.Command_Id).FirstOrDefault();

        if (properties == null) return Results.NoContent();

        var Commands = await db.Commands.FindAsync(properties.Command_Id);
        var Logs = await db.Logs.FindAsync(properties.Log_Id);

        if (Commands is null) return Results.NotFound();
        if (Logs is null) return Results.NotFound();

        Logs.Log_Text = (string?)a.Logs.Log_Text;
        Commands.Command_Performed = a.Command_Performed;

        await db.SaveChangesAsync();

        properties = (
                               from Commands1 in db.Commands.DefaultIfEmpty()
                               select new
                               {
                                   Command_Id = (int?)Commands1.Command_Id,
                                   Command_Performed = Commands1.Command_Performed,
                                   Command_String = Commands1.Command_String,
                                   Commands1.Command_Read,
                                   Log_Id = Commands1.Log_Id,
                                   Log_Text = Commands1.Logs.Log_Text

                               }).Where(b => b.Command_Id == Commands.Command_Id && b.Command_Read != null && b.Command_String != "RetrainModel").OrderBy(x => x.Command_Id).FirstOrDefault();

        return Results.Ok(properties);
    });
    //This route verify that the retrainmodel command is read but not performed.
    app.MapPut("/Commands/RetrainModel/Command_Performed", async (Commands a, CSSDb db) =>
    {
        var properties = (
                           from Commands1 in db.Commands.DefaultIfEmpty()
                           select new
                           {
                               Command_Id = (int?)Commands1.Command_Id,
                               Command_Performed = Commands1.Command_Performed,
                               Command_String = Commands1.Command_String,
                               Commands1.Command_Read,
                               Log_Id = Commands1.Log_Id,
                               Log_Text = Commands1.Logs.Log_Text

                           }).Where(b => b.Command_Performed == null && b.Command_Read != null && b.Command_String == "RetrainModel").OrderBy(x => x.Command_Id).FirstOrDefault();

        if (properties == null) return Results.NoContent();

        var Commands = await db.Commands.FindAsync(properties.Command_Id);
        var Logs = await db.Logs.FindAsync(properties.Log_Id);

        if (Commands is null) return Results.NotFound();
        if (Logs is null) return Results.NotFound();

        Logs.Log_Text = (string?)a.Logs.Log_Text;
        Commands.Command_Performed = a.Command_Performed;

        await db.SaveChangesAsync();
        properties = (
                           from Commands1 in db.Commands.DefaultIfEmpty()
                           select new
                           {
                               Command_Id = (int?)Commands1.Command_Id,
                               Command_Performed = Commands1.Command_Performed,
                               Command_String = Commands1.Command_String,
                               Commands1.Command_Read,
                               Log_Id = Commands1.Log_Id,
                               Log_Text = Commands1.Logs.Log_Text

                           }).Where(b => b.Command_Id == Commands.Command_Id && b.Command_Read != null && b.Command_String == "RetrainModel").OrderBy(x => x.Command_Id).FirstOrDefault();

        return Results.Ok(properties);
    });

    app.MapGet("/Commands/RetrainModel/Command_Performed/Verify", ( CSSDb db) =>
    {
         var properties = (
                    from Commands1 in db.Commands.DefaultIfEmpty()
                    select new
                    {
                        Command_Id = (int?)Commands1.Command_Id,
                        Command_Performed = Commands1.Command_Performed,
                        Command_String = Commands1.Command_String,
                        Commands1.Command_Read,
                        Log_Id = Commands1.Log_Id,
                        Log_Text = Commands1.Logs.Log_Text
                    }).Where(b => b.Command_String == "RetrainModel").OrderBy(x => x.Command_Id).LastOrDefault();
        if(properties != null) { Results.NoContent(); }

        return Results.Ok(properties);  


    });
//Delete a command by id.
    app.MapDelete("/Commands/{id:int}", async (int id, CSSDb db) =>
    {
        var Commands = await db.Commands.FindAsync(id);
        if (Commands is null) return Results.NotFound();

        db.Commands.Remove(Commands);
        await db.SaveChangesAsync();

        return Results.NoContent();
    });
//This route return the last command that has not been read.
    app.MapGet("/Commands/LastCommand", (CSSDb db) =>
    {
        var properties = (
                           from Commands in db.Commands.DefaultIfEmpty()
                           select new
                           {
                               Command_Id = (int?)Commands.Command_Id,
                               Command_Read = Commands.Command_Read,
                               Command_Performed = Commands.Command_Performed,
                               Command_String = Commands.Command_String,
                               Command_Value = Commands.Command_Value,
                               Command_Received = Commands.Command_Received,
                               Duplicate_Flag = Commands.Duplicate_Flag,
                               Log_Id = Commands.Log_Id,
                               AdminsUser_Id = Commands.AdminsUser_Id

                           });
        
        return Results.Ok(properties.Where(b => b.Command_Performed == null && b.Command_Read == null).OrderBy(x => x.Command_Id).FirstOrDefault());   

    });

    //Post an environmentaldata to the database
    app.MapPost("/EnvironmentalData/", async (EnvironmentalData a, CSSDb db) =>
    {
        db.EnvironmentalData.Add(a);
        await db.SaveChangesAsync();

        return Results.Created($"/EnvironmentalData/{a.Entry_Id}", a);
    });

    //Get environmentaldata by id.
    app.MapGet("/EnvironmentalData/{id:int}", async (int id, CSSDb db) =>
    {
        return await db.EnvironmentalData.FindAsync(id)
        is EnvironmentalData a
        ? Results.Ok(a)
        : Results.NotFound();

    });
    //This route filters the datetime that return the user.
    app.MapGet("/EnvironmentalData/Filter",  (string start,string end, CSSDb db) =>
    {
        var str = DateTimeOffset.Parse(start).AddHours(4);
        var en = DateTimeOffset.Parse(end).AddDays(1).AddHours(4);

        var properties = (from EnvironmentalData in db.EnvironmentalData.Where(x => x.Timestamps >= str && x.Timestamps <= en)
                          from Pictures in db.Pictures.Where(st => st.Pic_Id == EnvironmentalData.Pictures_Id).DefaultIfEmpty()
                          select new
                          {
                              EnvironmentalData.Entry_Id,
                              EnvironmentalData.Temperature,
                              EnvironmentalData.Humidity,
                              EnvironmentalData.Soil_Moisture_1,
                              EnvironmentalData.Soil_Moisture_2,
                              EnvironmentalData.Soil_Moisture_3,
                              EnvironmentalData.Soil_Moisture_4,
                              EnvironmentalData.Soil_Moisture_5,
                              EnvironmentalData.Soil_Moisture_6,
                              EnvironmentalData.Soil_Moisture_7,
                              EnvironmentalData.Soil_Moisture_8,
                              EnvironmentalData.Light,
                              EnvironmentalData.Reservoir_Water_Level,
                              EnvironmentalData.Timestamps,
                              EnvironmentalData.Water_Level,
                              EnvironmentalData.Pictures_Id,
                              Pic_Id = (int?)Pictures.Pic_Id,
                              Classification_Id_1 = (int?)Pictures.Classification_Id_1,
                              Classification_Id_2 = (int?)Pictures.Classification_Id_2,
                              Classification_Id_3 = (int?)Pictures.Classification_Id_3,
                              Classification_Id_4 = (int?)Pictures.Classification_Id_4
                          }).OrderByDescending(x => x.Entry_Id);

        return Results.Ok(properties);
    });

//get all environmentaldata including picture id and classification id in a descending form.
    app.MapGet("/EnvironmentalData/Classid",  (CSSDb db) =>
    {
        var properties = (from EnvironmentalData in db.EnvironmentalData
                          from Pictures in db.Pictures.Where(st => st.Pic_Id == EnvironmentalData.Pictures_Id)
                          select new
                          {
                              EnvironmentalData.Entry_Id,
                              EnvironmentalData.Temperature,
                              EnvironmentalData.Humidity,
                              EnvironmentalData.Soil_Moisture_1,
                              EnvironmentalData.Soil_Moisture_2,
                              EnvironmentalData.Soil_Moisture_3,
                              EnvironmentalData.Soil_Moisture_4,
                              EnvironmentalData.Soil_Moisture_5,
                              EnvironmentalData.Soil_Moisture_6,
                              EnvironmentalData.Soil_Moisture_7,
                              EnvironmentalData.Soil_Moisture_8,
                              EnvironmentalData.Light,
                              EnvironmentalData.Reservoir_Water_Level,
                              EnvironmentalData.Timestamps,
                              EnvironmentalData.Water_Level,
                              EnvironmentalData.Pictures_Id,
                              Pic_Id = (int?)Pictures.Pic_Id,
                              Classification_Id_1 = (int?)Pictures.Classification_Id_1,
                              Classification_Id_2 = (int?)Pictures.Classification_Id_2,
                              Classification_Id_3 = (int?)Pictures.Classification_Id_3,
                              Classification_Id_4 = (int?)Pictures.Classification_Id_4
                          }).OrderByDescending(x => x.Entry_Id).DefaultIfEmpty();

        return Results.Ok(properties);
    });

    //Get all environmentaldata 
    app.MapGet("/EnvironmentalDataAll",  (CSSDb db) => 
    {
        var properties = (
                          from EnvironmentalData in db.EnvironmentalData
                          select new
                          {
                              EnvironmentalData.Entry_Id,
                              EnvironmentalData.Temperature,
                              EnvironmentalData.Humidity,
                              EnvironmentalData.Soil_Moisture_1,
                              EnvironmentalData.Soil_Moisture_2,
                              EnvironmentalData.Soil_Moisture_3,
                              EnvironmentalData.Soil_Moisture_4,
                              EnvironmentalData.Soil_Moisture_5,
                              EnvironmentalData.Soil_Moisture_6,
                              EnvironmentalData.Soil_Moisture_7,
                              EnvironmentalData.Soil_Moisture_8,
                              EnvironmentalData.Light,
                              EnvironmentalData.Reservoir_Water_Level,
                              EnvironmentalData.Timestamps,
                              EnvironmentalData.Water_Level,
                              EnvironmentalData.Pictures_Id
                          }).DefaultIfEmpty();

        return Results.Ok(properties);
    });

    //Update environmentaldata from an existing id.
    app.MapPut("/EnvironmentalData/{id:int}", async (int id, EnvironmentalData a, CSSDb db) =>
    {
        var EnvironmentalData = await db.EnvironmentalData.FindAsync(id);

        if (EnvironmentalData is null) return Results.NotFound();

        EnvironmentalData.Entry_Id = a.Entry_Id;
        EnvironmentalData.Humidity = a.Humidity;
        EnvironmentalData.Temperature = a.Temperature;
        EnvironmentalData.Water_Level = a.Water_Level;
        EnvironmentalData.Light = a.Light;
        EnvironmentalData.Pictures_Id = a.Pictures_Id;
        EnvironmentalData.Soil_Moisture_1 = a.Soil_Moisture_1;
        EnvironmentalData.Soil_Moisture_2 = a.Soil_Moisture_2;
        EnvironmentalData.Soil_Moisture_3 = a.Soil_Moisture_3;
        EnvironmentalData.Soil_Moisture_4 = a.Soil_Moisture_4;
        EnvironmentalData.Soil_Moisture_5 = a.Soil_Moisture_5;
        EnvironmentalData.Soil_Moisture_6 = a.Soil_Moisture_6;
        EnvironmentalData.Soil_Moisture_7 = a.Soil_Moisture_7;
        EnvironmentalData.Soil_Moisture_8 = a.Soil_Moisture_8;
        EnvironmentalData.Reservoir_Water_Level = a.Reservoir_Water_Level;
        EnvironmentalData.Timestamps = a.Timestamps;


        await db.SaveChangesAsync();

        return Results.Ok(EnvironmentalData);
    });

    //Delete an existing envrionmentaldata by id.
    app.MapDelete("/EnvironmentalData/{id:int}", async (int id, CSSDb db) =>
    {
        var EnvironmentalData = await db.EnvironmentalData.FindAsync(id);

        if (EnvironmentalData is null) return Results.NotFound();

        db.EnvironmentalData.Remove(EnvironmentalData);

        await db.SaveChangesAsync();

        return Results.NoContent();
    });

    //Post a log to the database. 
    app.MapPost("/Logs/", async (Logs a, CSSDb db) =>
    {
        db.Logs.Add(a);

        await db.SaveChangesAsync();

        return Results.Created($"/Logs/{a.Log_Id}", a);
    });

    //Get log by id.
    app.MapGet("/Logs/{id:int}", async (int id, CSSDb db) =>
    {
        return await db.Logs.FindAsync(id)
        is Logs a
        ? Results.Ok(a)
        : Results.NotFound();

    });

    //Get all logs.
    app.MapGet("/LogsAll",  (CSSDb db) => db.Logs.OrderByDescending(x=>x.Log_Id).DefaultIfEmpty().ToListAsync());

    //Update an existing log by id.
    app.MapPut("/Logs/{id:int}", async (int id, Logs a, CSSDb db) =>
    {
        var Logs = await db.Logs.FindAsync(id);

        if (Logs is null) return Results.NotFound();

        Logs.Log_Id = a.Log_Id;
        Logs.Log_Text = a.Log_Text;
        Logs.Timestamps = a.Timestamps;

        await db.SaveChangesAsync();

        return Results.Ok(Logs);
    });

    //Delete log by id.
    app.MapDelete("/Logs/{id:int}", async (int id, CSSDb db) =>
    {
        var Logs = await db.Logs.FindAsync(id);

        if (Logs is null) return Results.NotFound();

        db.Logs.Remove(Logs);

        await db.SaveChangesAsync();

        return Results.NoContent();
    });

    //Post a pictures.
    app.MapPost("/Pictures/", async (Pictures a, CSSDb db) =>
    {
        db.Pictures.Add(a);

        await db.SaveChangesAsync();

        return Results.Created($"/admins/{a.Pic_Id}", a);
    });

    //Get pictures by id.
    app.MapGet("/Pictures/{id:int}", async (int id, CSSDb db) =>
    {
        return await db.Pictures.FindAsync(id)
        is Pictures a
        ? Results.Ok(a)
        : Results.NotFound();
    });
    //Get all pictures.
    app.MapGet("/PicturesAll",  (CSSDb db) =>  db.Pictures.OrderBy(x => x.Pic_Id).DefaultIfEmpty().ToListAsync());

    app.MapGet("/Pictures/Desc/Filter", (string start, string end, CSSDb db) =>
    {
        var str = DateTimeOffset.Parse(start).AddHours(4);
        var en = DateTimeOffset.Parse(end).AddDays(1).AddHours(4);

        var properties = (from Pictures in db.Pictures.Where(x => x.Timestamps >= str && x.Timestamps <= en)
                       select new
                       {
                           Pic_Id = (int?)Pictures.Pic_Id,
                           Camera_Pic_Path_1 = Pictures.Camera_Pic_Path_1,
                           Camera_Pic_Path_2 = Pictures.Camera_Pic_Path_2,
                           Camera_Pic_Path_3 = Pictures.Camera_Pic_Path_3,
                           Camera_Pic_Path_4 = Pictures.Camera_Pic_Path_4,
                           Classification_Accurracy_1 = Pictures.Classification_Accurracy_1,
                           Classification_Accurracy_2 = Pictures.Classification_Accurracy_2,
                           Classification_Accurracy_3 = Pictures.Classification_Accurracy_3,
                           Classification_Accurracy_4 = Pictures.Classification_Accurracy_4,
                           Classification_Id_1 = Pictures.Classification_Id_1,
                           Classification_Id_2 = Pictures.Classification_Id_2,
                           Classification_Id_3 = Pictures.Classification_Id_3,
                           Classification_Id_4 = Pictures.Classification_Id_4,
                           Timestamps = Pictures.Timestamps
                       }).OrderByDescending(x => x.Pic_Id);

     return Results.Ok(properties);
    });
//Get all pictures descending.
    app.MapGet("/Pictures/Desc",  (CSSDb db) =>
    {
        var properties = (
                    from Pictures in db.Pictures
                    select new
                    {
                        Pic_Id = (int?)Pictures.Pic_Id,
                        Camera_Pic_Path_1 = Pictures.Camera_Pic_Path_1,
                        Camera_Pic_Path_2 = Pictures.Camera_Pic_Path_2,
                        Camera_Pic_Path_3 = Pictures.Camera_Pic_Path_3,
                        Camera_Pic_Path_4 = Pictures.Camera_Pic_Path_4,
                        Classification_Accurracy_1 = Pictures.Classification_Accurracy_1,
                        Classification_Accurracy_2 = Pictures.Classification_Accurracy_2,
                        Classification_Accurracy_3 = Pictures.Classification_Accurracy_3,
                        Classification_Accurracy_4 = Pictures.Classification_Accurracy_4,
                        Classification_Id_1 = Pictures.Classification_Id_1,
                        Classification_Id_2 = Pictures.Classification_Id_2,
                        Classification_Id_3 = Pictures.Classification_Id_3,
                        Classification_Id_4 = Pictures.Classification_Id_4,
                        Timestamps = Pictures.Timestamps
                    }).OrderByDescending(x => x.Pic_Id);
    
        return Results.Ok(properties);
    });

//Update pictures data from an existind id.
    app.MapPut("/Pictures/{id:int}", async (int id, Pictures a, CSSDb db) =>
    {
        var Pictures = await db.Pictures.FindAsync(id);

        if (Pictures is null) return Results.NotFound();
        /* 
         * These if are defining if the user makes any change in any of the variables of the sent id.
         */
        Pictures.Classification_Accurracy_1 = a.Classification_Accurracy_1 != null ? a.Classification_Accurracy_1 : Pictures.Classification_Accurracy_1;
        Pictures.Classification_Accurracy_2 = a.Classification_Accurracy_2 != null ? a.Classification_Accurracy_2 : Pictures.Classification_Accurracy_2;
        Pictures.Classification_Accurracy_3 = a.Classification_Accurracy_3 != null ? a.Classification_Accurracy_3 : Pictures.Classification_Accurracy_3;
        Pictures.Classification_Accurracy_4 = a.Classification_Accurracy_4 != null ? a.Classification_Accurracy_4 : Pictures.Classification_Accurracy_4;

        Pictures.Classification_Id_1 = a.Classification_Id_1 != null ? a.Classification_Id_1 : Pictures.Classification_Id_1;
        Pictures.Classification_Id_2 = a.Classification_Id_2 != null ? a.Classification_Id_2 : Pictures.Classification_Id_2;
        Pictures.Classification_Id_3 = a.Classification_Id_3 != null ? a.Classification_Id_3 : Pictures.Classification_Id_3;
        Pictures.Classification_Id_4 = a.Classification_Id_4 != null ? a.Classification_Id_4 : Pictures.Classification_Id_4;

        await db.SaveChangesAsync();
        return Results.Ok(Pictures);
    });

    //Delete picture by id.
    app.MapDelete("/Pictures/{id:int}", async (int id, CSSDb db) =>
    {
        //This lines finds the id received and If that id is not found the response will be 404.
        var Pictures = await db.Pictures.FindAsync(id);
        if (Pictures is null) return Results.NotFound();

        //If is found the entity will be removed.
        db.Pictures.Remove(Pictures);
        await db.SaveChangesAsync();

        return Results.NoContent();
    });


    //This route delete all the rows of all tables and reset the index.
    app.MapDelete("/Delete/all", async (CSSDb db) =>
    { //Send a raw sql query to the postgresql server.
        db.Database.ExecuteSqlRaw("TRUNCATE TABLE Public.\"Admins\",Public.\"Commands\",Public.\"EnvironmentalData\",Public.\"Logs\",Public.\"Pictures\" RESTART IDENTITY;");
    });


    //This routes delete all the rows of the tables Commands and Logs.
    app.MapDelete("/Delete/allCommands&Logs", async (CSSDb db) =>
    {   //Send a raw sql query to the postgresql server.
        db.Database.ExecuteSqlRaw("TRUNCATE TABLE public.\"Commands\",public.\"Logs\" RESTART IDENTITY;");
    });

app.MapDelete("/Delete/allEnvironmentalData&Pictures", async (CSSDb db) =>
{ //Send a raw sql query to the postgresql server.
    db.Database.ExecuteSqlRaw("TRUNCATE TABLE Public.\"EnvironmentalData\",Public.\"Pictures\" RESTART IDENTITY;");
});

app.Run();


