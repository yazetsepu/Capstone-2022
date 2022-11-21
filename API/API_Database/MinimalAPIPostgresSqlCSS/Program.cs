using Microsoft.AspNetCore.Builder;
using Microsoft.EntityFrameworkCore;
using MinimalAPIPostgresSqlCSS.Data;
using MinimalAPIPostgresSqlCSS.Models;
using System.Security.Cryptography;
using System.Text.Json.Serialization;
using System.Web.Http.Results;

var MyAllowSpecificOrigins = "_myAllowSpecificOrigins";
var builder = WebApplication.CreateBuilder(args);

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
//Agregando un contenedor de dependencias usando postgres
builder.Services.AddDbContext<CSSDb>(options =>
options.UseNpgsql(connectionString));


var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

//app.UseHttpsRedirection();

app.UseCors(MyAllowSpecificOrigins);



//HttpPost Admin table David Ortiz
app.MapPost("/Admins/", async (Admins a, CSSDb db) =>
{
    
    db.Admins.Add(a);
    await db.SaveChangesAsync();

    return Results.Created($"/Admins/{a.User_Id}", a);
});

app.MapGet("/Admins/{id:int}", async (int id, CSSDb db) =>
{
    return await db.Admins.FindAsync(id)
    is Admins a
    ? Results.Ok(a)
    : Results.NotFound();

});

app.MapGet("/AdminsAll", async (CSSDb db) =>await db.Admins.ToListAsync());

app.MapPut("/Admins/{id:int}", async (int id, Admins a, CSSDb db) =>
{

   // if (a.User_Id != id) return Results.BadRequest();



    var admins = await db.Admins.FindAsync(id);

    if (admins is null) return Results.NotFound();  
    
    admins.User_Id = a.User_Id;
    admins.Admin_Email = a.Admin_Email;
    admins.Admin_Password = a.Admin_Password;

    await db.SaveChangesAsync();
    return Results.Ok(admins);



});

app.MapDelete("/Admins/{id:int}", async (int id, CSSDb db) =>
{
    var admins = await db.Admins.FindAsync(id);
    if (admins is null) return Results.NotFound();
    
        db.Admins.Remove(admins);
        await db.SaveChangesAsync();
    
    return Results.NoContent();
});

app.MapGet("/Admins/Commands/{id:int}", async (int id, CSSDb db)  =>
{
    var properties = (from Commands in db.Commands.Where(st => st.AdminsUser_Id == id).DefaultIfEmpty()
                      select new
                      {
                          AdminsUser_Id = (int?)Commands.AdminsUser_Id,
                          Command_Id = (int?)Commands.Command_Id,
                          Command_string = (string?)Commands.Command_String
                          

                      }); ;

    if (Results.Ok(properties)==null)
    {
        return Results.NotFound();
    }
    else
    {
        return Results.Ok(properties);
    }
    
    
});

//HttpPost Commands table David Ortiz
app.MapPost("/Commands/", async (Commands a, CSSDb db) =>
{
    db.Commands.Add(a);
    await db.SaveChangesAsync();

    return Results.Created($"/admins/{a.Command_Id}", a);
});

app.MapGet("/Commands/{id:int}", async (int id, CSSDb db) =>
{
    return await db.Commands.FindAsync(id)
    is Commands a
    ? Results.Ok(a)
    : Results.NotFound();

});

app.MapGet("/CommandsAll", async (CSSDb db) => await db.Commands.ToListAsync());

app.MapPut("/Commands/{id:int}", async (int id, Commands a, CSSDb db) =>
{

    // if (a.User_Id != id) return Results.BadRequest();



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

app.MapPut("/Commands/Command_Read/{id:int}", async (int id, Commands a, CSSDb db) =>
{

    // if (a.User_Id != id) return Results.BadRequest();



    var Commands = await db.Commands.FindAsync(id);

    if (Commands is null) return Results.NotFound();
    

    Commands.Command_Read = a.Command_Read;

    await db.SaveChangesAsync();
    return Results.Ok(Commands);



});
app.MapPut("/Commands/Command_Performed/{id:int}", async (int id, Commands a, CSSDb db) =>
{

    // if (a.User_Id != id) return Results.BadRequest();



    var Commands = await db.Commands.FindAsync(id);

    if (Commands is null) return Results.NotFound();
    

    Commands.Command_Performed = a.Command_Performed;

    await db.SaveChangesAsync();
    return Results.Ok(Commands);



});
app.MapDelete("/Commands/{id:int}", async (int id, CSSDb db) =>
{
    var Commands = await db.Commands.FindAsync(id);
    if (Commands is null) return Results.NotFound();

    db.Commands.Remove(Commands);
    await db.SaveChangesAsync();

    return Results.NoContent();
});


//HttpPost EnvironmentalData table David Ortiz
app.MapPost("/EnvironmentalData/", async (EnvironmentalData a, CSSDb db) =>
{
    db.EnvironmentalData.Add(a);
    await db.SaveChangesAsync();

    return Results.Created($"/EnvironmentalData/{a.Entry_Id}", a);
});

app.MapGet("/EnvironmentalData/{id:int}", async (int id, CSSDb db) =>
{
    return await db.EnvironmentalData.FindAsync(id)
    is EnvironmentalData a
    ? Results.Ok(a)
    : Results.NotFound();

});
//new code
/*
app.MapGet("/EnvironmentalData/classidTest", async ( CSSDb db) =>
{

    var properties = db.EnvironmentalData
    .Join(db.Pictures,
      p => p.Pictures_Id,
      d => d.Pic_Id,
      (p, d) => new
      {
          p.Entry_Id,
          p.Water_Level,
          p.Temperature,
          p.Soil_Moisture_1,
          p.Humidity,
          p.Timestamps,
          d.Pic_Id,
          d.Classification_Id_1

      })
   .Select(r => new
   {
       Entry_Id = r.Entry_Id,
       Water_Level = r.Water_Level,
       Temperature = r.Temperature,
       Soil_Moisture_1 = r.Soil_Moisture_1,
       Humidity = r.Humidity,
       Timestamps = r.Timestamps,
       Pic_Id = r.Pic_Id,
       Classification_Id_1 =r.Classification_Id_1

   });
    
  return  Results.Ok(properties);
   
});*/
/*
app.MapGet("/EnvironmentalData/classidTest2", async (CSSDb db) =>
{

    var properties = from EnvironmentalData in db.EnvironmentalData
                     join Pictures in db.Pictures
                     on EnvironmentalData.Pictures_Id equals Pictures.Pic_Id into grouping
                     from Pictures in grouping.DefaultIfEmpty()
                     select new { Enviromental = EnvironmentalData, Picture= Pictures };


    return Results.Ok(properties);

});*/
app.MapGet("/EnvironmentalData/Classid", async (CSSDb db) =>
{

    var properties = (from EnvironmentalData in db.EnvironmentalData
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
                          Classification_id = (int?)Pictures.Classification_Id_1

                      }).OrderByDescending(x =>x.Entry_Id);

    return Results.Ok(properties);

});
app.MapGet("/EnvironmentalDataAll", async (CSSDb db) => await db.EnvironmentalData.ToListAsync());

app.MapPut("/EnvironmentalData/{id:int}", async (int id, EnvironmentalData a, CSSDb db) =>
{

    // if (a.User_Id != id) return Results.BadRequest();



    var EnvironmentalData = await db.EnvironmentalData.FindAsync(id);

    if (EnvironmentalData is null) return Results.NotFound();

    EnvironmentalData.Entry_Id = a.Entry_Id;
    EnvironmentalData.Humidity = a.Humidity;
    EnvironmentalData.Temperature = a.Temperature;
    EnvironmentalData.Water_Level = a.Water_Level;
    EnvironmentalData.Light = a.Light;
    EnvironmentalData.Pictures_Id = a.Pictures_Id;
    EnvironmentalData.Soil_Moisture_1 = a.Soil_Moisture_1;
    EnvironmentalData.Soil_Moisture_2=a.Soil_Moisture_2;
    EnvironmentalData.Soil_Moisture_3 = a.Soil_Moisture_3;    
    EnvironmentalData.Soil_Moisture_4=a.Soil_Moisture_4;
    EnvironmentalData.Soil_Moisture_5=a.Soil_Moisture_5;
    EnvironmentalData.Soil_Moisture_6=a.Soil_Moisture_6;
    EnvironmentalData.Soil_Moisture_7=a.Soil_Moisture_7;
    EnvironmentalData.Soil_Moisture_8=a.Soil_Moisture_8;
    EnvironmentalData.Reservoir_Water_Level=a.Reservoir_Water_Level;
    EnvironmentalData.Timestamps = a.Timestamps;
   

    await db.SaveChangesAsync();
    return Results.Ok(EnvironmentalData);



});

app.MapDelete("/EnvironmentalData/{id:int}", async (int id, CSSDb db) =>
{
    var EnvironmentalData = await db.EnvironmentalData.FindAsync(id);
    if (EnvironmentalData is null) return Results.NotFound();

    db.EnvironmentalData.Remove(EnvironmentalData);
    await db.SaveChangesAsync();

    return Results.NoContent();
});

//HttpPost Logs table David Ortiz
app.MapPost("/Logs/", async (Logs a, CSSDb db) =>
{
    db.Logs.Add(a);
    await db.SaveChangesAsync();

    return Results.Created($"/Logs/{a.Log_Id}", a);
});

app.MapGet("/Logs/{id:int}", async (int id, CSSDb db) =>
{
    return await db.Logs.FindAsync(id)
    is Logs a
    ? Results.Ok(a)
    : Results.NotFound();

});

app.MapGet("/LogsAll", async (CSSDb db) => await db.Logs.ToListAsync());

app.MapPut("/Logs/{id:int}", async (int id, Logs a, CSSDb db) =>
{

    // if (a.User_Id != id) return Results.BadRequest();



    var Logs = await db.Logs.FindAsync(id);

    if (Logs is null) return Results.NotFound();

    Logs.Log_Id = a.Log_Id;
    Logs.Log_Text = a.Log_Text;
    Logs.Timestamps = a.Timestamps;
    

    await db.SaveChangesAsync();
    return Results.Ok(Logs);



});

app.MapDelete("/Logs/{id:int}", async (int id, CSSDb db) =>
{
    var Logs = await db.Logs.FindAsync(id);
    if (Logs is null) return Results.NotFound();

    db.Logs.Remove(Logs);
    await db.SaveChangesAsync();

    return Results.NoContent();
});

//HttpPost Picture table David Ortiz
app.MapPost("/Pictures/", async (Pictures a, CSSDb db) =>
{  
    db.Pictures.Add(a);
    await db.SaveChangesAsync();

    return Results.Created($"/admins/{a.Pic_Id}", a);
});

app.MapGet("/Pictures/{id:int}", async (int id, CSSDb db) =>
{
    return await db.Pictures.FindAsync(id)
    is Pictures a
    ? Results.Ok(a)
    : Results.NotFound();

});

app.MapGet("/PicturesAll", async (CSSDb db) => await db.Pictures.ToListAsync());

app.MapGet("/Pictures/Desc", async (CSSDb db) =>
{

    var properties = (
                      from Pictures in db.Pictures.DefaultIfEmpty()
                      select new
                      {
                          Pic_Id = (int?)Pictures.Pic_Id,
                          Camera_Pic_Path_1 = Pictures.Camera_Pic_Path_1,
                          Camera_Pic_Path_2= Pictures.Camera_Pic_Path_2,    
                          Camera_Pic_Path_3= Pictures.Camera_Pic_Path_3,    
                          Camera_Pic_Path_4= Pictures.Camera_Pic_Path_4,
                          Classification_accurracy=Pictures.Classification_Accurracy_1,
                          Classification_accurracy_2=Pictures.Classification_Accurracy_2,
                          Classification_accurracy_3= Pictures.Classification_Accurracy_3,
                          Classification_accurracy_4= Pictures.Classification_Accurracy_4,
                          Classification_id=Pictures.Classification_Id_1,
                          Classification_id_2=Pictures.Classification_Id_2,
                          Classification_id_3=Pictures.Classification_Id_3,
                          Classification_id_4=Pictures.Classification_Id_4,
                          Times_tamps=Pictures.Timestamps


                      }).OrderByDescending(x => x.Pic_Id);

    return Results.Ok(properties);

});

app.MapPut("/Pictures/{id:int}", async (int id, Pictures a, CSSDb db) =>
{

    // if (a.User_Id != id) return Results.BadRequest();



    var Pictures = await db.Pictures.FindAsync(id);

    if (Pictures is null) return Results.NotFound();

    Pictures.Pic_Id = a.Pic_Id;
    Pictures.Classification_Accurracy_1 = a.Classification_Accurracy_1;
    Pictures.Classification_Accurracy_2 = a.Classification_Accurracy_2;
    Pictures.Classification_Accurracy_3 = a.Classification_Accurracy_3;
    Pictures.Classification_Accurracy_4 = a.Classification_Accurracy_4;
    Pictures.Classification_Id_1 = a.Classification_Id_1;
    Pictures.Classification_Id_2 = a.Classification_Id_2;
    Pictures.Classification_Id_3 = a.Classification_Id_3;
    Pictures.Classification_Id_4 = a.Classification_Id_4;
    Pictures.Camera_Pic_Path_1 = a.Camera_Pic_Path_1;
    Pictures.Camera_Pic_Path_2 = a.Camera_Pic_Path_2;
    Pictures.Camera_Pic_Path_3 = a.Camera_Pic_Path_3;
    Pictures.Camera_Pic_Path_4 = a.Camera_Pic_Path_4;
    Pictures.Timestamps = a.Timestamps;
    


   

    await db.SaveChangesAsync();
    return Results.Ok(Pictures);



});

app.MapDelete("/Pictures/{id:int}", async (int id, CSSDb db) =>
{
    var Pictures = await db.Pictures.FindAsync(id);
    if (Pictures is null) return Results.NotFound();

    db.Pictures.Remove(Pictures);
    await db.SaveChangesAsync();

    return Results.NoContent();
});


app.Run();