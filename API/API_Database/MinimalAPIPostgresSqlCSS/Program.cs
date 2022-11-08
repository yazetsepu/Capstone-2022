using Microsoft.EntityFrameworkCore;
using MinimalAPIPostgresSqlCSS.Data;
using MinimalAPIPostgresSqlCSS.Models;

var builder = WebApplication.CreateBuilder(args);

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

app.UseHttpsRedirection();





//HttpPost Admin table David Ortiz
app.MapPost("/admins/", async (Admins a, CSSDb db) =>
{
    
    db.Admins.Add(a);
    await db.SaveChangesAsync();

    return Results.Created($"/admins/{a.User_Id}", a);
});

app.MapGet("/admins/{id:int}", async (int id, CSSDb db) =>
{
    return await db.Admins.FindAsync(id)
    is Admins a
    ? Results.Ok(a)
    : Results.NotFound();

});

app.MapGet("/adminsAll", async (CSSDb db) =>await db.Admins.ToListAsync());

app.MapPut("/admins/{id:int}", async (int id, Admins a, CSSDb db) =>
{

   // if (a.User_id != id) return Results.BadRequest();



    var admins = await db.Admins.FindAsync(id);

    if (admins is null) return Results.NotFound();  
    
    admins.User_Id = a.User_Id;
    admins.Admin_Email = a.Admin_Email;
    admins.Admin_Password = a.Admin_Password;

    await db.SaveChangesAsync();
    return Results.Ok(admins);



});

app.MapDelete("/admins/{id:int}", async (int id, CSSDb db) =>
{
    var admins = await db.Admins.FindAsync(id);
    if (admins is null) return Results.NotFound();
    
        db.Admins.Remove(admins);
        await db.SaveChangesAsync();
    
    return Results.NoContent();
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

    // if (a.User_id != id) return Results.BadRequest();



    var Commands = await db.Commands.FindAsync(id);

    if (Commands is null) return Results.NotFound();

    Commands.Command_Id = a.Command_Id;
    Commands.Command_string = a.Command_string;
    Commands.Command_value = a.Command_value;
    Commands.Command_received = a.Command_received;
    Commands.Command_performed = a.Command_performed;
    Commands.Command_read = a.Command_read;
    Commands.Duplicate_flag = a.Duplicate_flag;
  

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

app.MapGet("/EnvironmentalDataAll", async (CSSDb db) => await db.EnvironmentalData.ToListAsync());

app.MapPut("/EnvironmentalData/{id:int}", async (int id, EnvironmentalData a, CSSDb db) =>
{

    // if (a.User_id != id) return Results.BadRequest();



    var EnvironmentalData = await db.EnvironmentalData.FindAsync(id);

    if (EnvironmentalData is null) return Results.NotFound();

    EnvironmentalData.Entry_Id = a.Entry_Id;
    EnvironmentalData.Humidity = a.Humidity;
    EnvironmentalData.Temperature = a.Temperature;
    EnvironmentalData.Water_level = a.Water_level;
    EnvironmentalData.Soil_moisture = a.Soil_moisture;
    EnvironmentalData.Times_tamps = a.Times_tamps;
   

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

    return Results.Created($"/Logs/{a.Log_id}", a);
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

    // if (a.User_id != id) return Results.BadRequest();



    var Logs = await db.Logs.FindAsync(id);

    if (Logs is null) return Results.NotFound();

    Logs.Log_id = a.Log_id;
    Logs.Log_text = a.Log_text;
    Logs.Times_tamps = a.Times_tamps;
    

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

app.MapPut("/Pictures/{id:int}", async (int id, Pictures a, CSSDb db) =>
{

    // if (a.User_id != id) return Results.BadRequest();



    var Pictures = await db.Pictures.FindAsync(id);

    if (Pictures is null) return Results.NotFound();

    Pictures.Pic_Id = a.Pic_Id;
    Pictures.Classification_accurracy = a.Classification_accurracy;
    Pictures.Classification_id = a.Classification_id;
    Pictures.Clock = a.Clock;


   

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



internal record WeatherForecast(DateTime Date, int TemperatureC, string? Summary)
{
    public int TemperatureF => 32 + (int)(TemperatureC / 0.5556);
}