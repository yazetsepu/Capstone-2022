
# Welcome to CSSRUMAPI!

This API is based on **dotNet 6**, it uses the C# programming language. This API is a **minimal Entity Framework API**, which creates a graphical interface that allows us to see all the routes and use them, providing examples of the JSON. This GUI is based on **Swagger UI**.

# Database
This **API** through the framework allows you to create models of what the tables will be, allowing you to use a tool to create them. 

**PostgreSQL** is being used as an object-oriented relational database management system and is also open source.

>Example pic of model on the MinimalAPI Entity Framework. 
![Admin model example](https://user-images.githubusercontent.com/31049645/200149210-53625132-3869-4385-9f29-90f8c4e6c658.png)



# API Description
**Dependencies:**
As part of the necessary packages and installation of dependencies:

>Microsoft:
>
>**Microsoft.AspNetCore.Diagnostics.EntityFrameworkCore
>Microsoft.EntityFrameworkCore
>Microsoft.EntityFrameworkCore.Design**

>Npgsql:
>
>**Npgsql.EntityFrameworkCore.PostgreSQL**

>Swashbuckle:
>
>**Swashbuckle.AspNetCore**

**Frameworks:**
>Microsoft.AspNetCore.App
>Microsoft.NETCore.APP

**API Connection String:**
  "ConnectionStrings": {
    "PostgreSQLConnection": 
    "Server=chamaecristarum.postgres.database.azure.com;
     Port=5432;
     Database=CSSRUMDb;User 
     Id=chamaecristaadmin;
     Password=*****************;
     Ssl Mode=VerifyFull;" }
}



**Migrations commands for table creation:**

>cd .\MinimalAPIPostgresSqlCSS
>
>dotnet tool install --global dotnet-ef 
>
>dotnet ef migrations add firstmigration --project MinimalAPIPostgresSqlCSS.csproj
>
>dotnet ef database update firstmigration --project MinimalAPIPostgresSqlCSS.csproj
>



**Db Context for EntityFrameworkCore Creation:**
![image](https://user-images.githubusercontent.com/31049645/202927961-b1c08b90-d67b-4e04-925d-7d0844c3de8d.png)


**Routes and API JSON examples:**

#Table Schemas:
Admins:

![image](https://user-images.githubusercontent.com/31049645/203210890-8d8b1287-f3bf-43fc-ae25-9ae5bc42a505.png)

Commands:

![image](https://user-images.githubusercontent.com/31049645/203210934-a125bf7a-a698-4082-8954-c98b2f397f08.png)

EnvironmentalData:

![image](https://user-images.githubusercontent.com/31049645/203210981-bfad4ee4-6c49-46ad-a58f-8d4a274bfc17.png)

Logs:

![image](https://user-images.githubusercontent.com/31049645/203211009-5141898e-b889-476e-b888-06cc78fa4494.png)

Pictures:

![image](https://user-images.githubusercontent.com/31049645/203211027-76a4165a-cab3-4765-9c22-84e11eafaeba.png)

# Routes:
## Admins
admins:Post/
https://cssrumapi.azurewebsites.net/admins
```json
{
  "user_Id": 0,
  "admin_Email": "string",
  "admin_Password": "string",
  "commands": [
    {
      "command_Id": 0,
      "log_Id": 0,
      "adminsUser_Id": 0,
      "duplicate_Flag": 0,
      "command_String": "string",
      "command_Value": "string",
      "admins": "string",
      "logs": {
        "log_Id": 0,
        "log_Text": "string",
        "timestamps": "2022-11-22T03:04:15.226Z"
      },
      "command_Received": "2022-11-22T03:04:15.226Z",
      "command_Read": "2022-11-22T03:04:15.226Z",
      "command_Performed": "2022-11-22T03:04:15.226Z"
    }
  ]
}
```

admins:get by id
https://cssrumapi.azurewebsites.net/admins/1

admins: put by id
https://cssrumapi.azurewebsites.net/admins/1
```json
{
  "user_Id": 0,
  "admin_Email": "string",
  "admin_Password": "string",
  "commands": [
    {
      "command_Id": 0,
      "log_Id": 0,
      "adminsUser_Id": 0,
      "duplicate_Flag": 0,
      "command_String": "string",
      "command_Value": "string",
      "admins": "string",
      "logs": {
        "log_Id": 0,
        "log_Text": "string",
        "timestamps": "2022-11-22T03:04:15.226Z"
      },
      "command_Received": "2022-11-22T03:04:15.226Z",
      "command_Read": "2022-11-22T03:04:15.226Z",
      "command_Performed": "2022-11-22T03:04:15.226Z"
    }
  ]
}
```
admins: delete by id
https://cssrumapi.azurewebsites.net/admins/1

admins: admins get all
https://cssrumapi.azurewebsites.net/adminsall

admins: admins commands by id
https://cssrumapi.azurewebsites.net/admins/commands/1

## Commands
commands: post
https://cssrumapi.azurewebsites.net/commands/
```json
{
  "command_Id": 0,
  "log_Id": 0,
  "adminsUser_Id": 0,
  "duplicate_Flag": 0,
  "command_String": "string",
  "command_Value": "string",
  "admins": {
    "user_Id": 0,
    "admin_Email": "string",
    "admin_Password": "string",
    "commands": [
      "string"
    ]
  },
  "logs": {
    "log_Id": 0,
    "log_Text": "string",
    "timestamps": "2022-11-22T03:05:03.580Z"
  },
  "command_Received": "2022-11-22T03:05:03.580Z",
  "command_Read": "2022-11-22T03:05:03.580Z",
  "command_Performed": "2022-11-22T03:05:03.580Z"
}
```
commands: get by id
https://cssrumapi.azurewebsites.net/commands/1

commands: put by commands
https://cssrumapi.azurewebsites.net/commands/1
```json
{
  "command_Id": 0,
  "log_Id": 0,
  "adminsUser_Id": 0,
  "duplicate_Flag": 0,
  "command_String": "string",
  "command_Value": "string",
  "admins": {
    "user_Id": 0,
    "admin_Email": "string",
    "admin_Password": "string",
    "commands": [
      "string"
    ]
  },
  "logs": {
    "log_Id": 0,
    "log_Text": "string",
    "timestamps": "2022-11-22T03:05:03.580Z"
  },
  "command_Received": "2022-11-22T03:05:03.580Z",
  "command_Read": "2022-11-22T03:05:03.580Z",
  "command_Performed": "2022-11-22T03:05:03.580Z"
}
```
commands: delete by id 
https://cssrumapi.azurewebsites.net/commands/1

commands: get all commands
https://cssrumapi.azurewebsites.net/commandsAll

commands: put commands_read
https://cssrumapi.azurewebsites.net/commands/Command_read
```json
{
//This have to be blank.
}
```

commands: put commands_performed
https://cssrumapi.azurewebsites.net/commands/Command_performed
```json
{
  "logs": {
    "log_Text": "string"
  }
}
```

commands: put RetrainModel/commands_read
https://cssrumapi.azurewebsites.net/Commands/RetrainModel/Command_read
```json
{
//This have to be blank.
}
```

commands: put RetrainModel/commands_performed
https://cssrumapi.azurewebsites.net/Commands/RetrainModel/Command_performed
```json
{
  "logs": {
    "log_Text": "string"
  }
}
```

commands: get RetrainModel/commands_performed/Verify
https://cssrumapi.azurewebsites.net/Commands/RetrainModel/Command_performed/Verify

commands: get Commands/LastCommand
https://cssrumapi.azurewebsites.net/Commands/LastCommand

## EnvironmentalData

environmentaldata:Post
https://cssrumapi.azurewebsites.net/Environmentaldata
```json
{
  "entry_Id": 0,
  "pictures_Id": 0,
  "water_Level": 0,
  "temperature": 0,
  "soil_Moisture_1": 0,
  "soil_Moisture_2": 0,
  "soil_Moisture_3": 0,
  "soil_Moisture_4": 0,
  "soil_Moisture_5": 0,
  "soil_Moisture_6": 0,
  "soil_Moisture_7": 0,
  "soil_Moisture_8": 0,
  "humidity": 0,
  "light": 0,
  "reservoir_Water_Level": "string",
  "pictures": {
    "pic_Id": 0,
    "classification_Id_1": 0,
    "classification_Id_2": 0,
    "classification_Id_3": 0,
    "classification_Id_4": 0,
    "classification_Accurracy_1": 0,
    "classification_Accurracy_2": 0,
    "classification_Accurracy_3": 0,
    "classification_Accurracy_4": 0,
    "camera_Pic_Path_1": "string",
    "camera_Pic_Path_2": "string",
    "camera_Pic_Path_3": "string",
    "camera_Pic_Path_4": "string",
    "timestamps": "2022-11-22T03:05:22.703Z"
  },
  "timestamps": "2022-11-22T03:05:22.703Z"
}

```

environmentaldata:Get by id
https://cssrumapi.azurewebsites.net/environmentaldata/1

environmentaldata:Put by id
https://cssrumapi.azurewebsites.net/environmentaldata/1
```json
{
  "entry_Id": 0,
  "pictures_Id": 0,
  "water_Level": 0,
  "temperature": 0,
  "soil_Moisture_1": 0,
  "soil_Moisture_2": 0,
  "soil_Moisture_3": 0,
  "soil_Moisture_4": 0,
  "soil_Moisture_5": 0,
  "soil_Moisture_6": 0,
  "soil_Moisture_7": 0,
  "soil_Moisture_8": 0,
  "humidity": 0,
  "light": 0,
  "reservoir_Water_Level": "string",
  "pictures": {
    "pic_Id": 0,
    "classification_Id_1": 0,
    "classification_Id_2": 0,
    "classification_Id_3": 0,
    "classification_Id_4": 0,
    "classification_Accurracy_1": 0,
    "classification_Accurracy_2": 0,
    "classification_Accurracy_3": 0,
    "classification_Accurracy_4": 0,
    "camera_Pic_Path_1": "string",
    "camera_Pic_Path_2": "string",
    "camera_Pic_Path_3": "string",
    "camera_Pic_Path_4": "string",
    "timestamps": "2022-11-22T03:05:22.703Z"
  },
  "timestamps": "2022-11-22T03:05:22.703Z"
}

```

environmentaldata:delete by id
https://cssrumapi.azurewebsites.net/environmentaldata/1

environmentaldata: get all with Filter
https://cssrumapi.azurewebsites.net/environmentaldata/Filter

environmentaldata: get all with classid
https://cssrumapi.azurewebsites.net/environmentaldata/classid

environmentaldata: get all 
https://cssrumapi.azurewebsites.net/environmentaldataall

## Logs
logs:post
https://cssrumapi.azurewebsites.net/Logs
```json
{
  "log_Id": 0,
  "log_Text": "string",
  "timestamps": "2022-11-22T03:05:42.531Z"
}
```
logs: get  by id
https://cssrumapi.azurewebsites.net/logs/1

logs: put  by id
https://cssrumapi.azurewebsites.net/logs/1
```json
{
  "log_Id": 0,
  "log_Text": "string",
  "timestamps": "2022-11-22T03:05:42.531Z"
}
```
logs: delete  by id
https://cssrumapi.azurewebsites.net/logs/1

logs: get all 
https://cssrumapi.azurewebsites.net/logsall

## Picture
Pictures: get  by id
https://cssrumapi.azurewebsites.net/Pictures/1
```json
{
  "pic_Id": 0,
  "classification_Id_1": 0,
  "classification_Id_2": 0,
  "classification_Id_3": 0,
  "classification_Id_4": 0,
  "classification_Accurracy_1": 0,
  "classification_Accurracy_2": 0,
  "classification_Accurracy_3": 0,
  "classification_Accurracy_4": 0,
  "camera_Pic_Path_1": "string",
  "camera_Pic_Path_2": "string",
  "camera_Pic_Path_3": "string",
  "camera_Pic_Path_4": "string",
  "timestamps": "2022-11-22T03:05:55.097Z"
}
```
Pictures: get  by id
https://cssrumapi.azurewebsites.net/Pictures/1

Pictures: put  by id
https://cssrumapi.azurewebsites.net/Pictures/1
```json
{
  "pic_Id": 0,
  "classification_Id_1": 0,
  "classification_Id_2": 0,
  "classification_Id_3": 0,
  "classification_Id_4": 0,
  "classification_Accurracy_1": 0,
  "classification_Accurracy_2": 0,
  "classification_Accurracy_3": 0,
  "classification_Accurracy_4": 0,
  "camera_Pic_Path_1": "string",
  "camera_Pic_Path_2": "string",
  "camera_Pic_Path_3": "string",
  "camera_Pic_Path_4": "string",
  "timestamps": "2022-11-22T03:05:55.097Z"
}
```
Pictures: delete  by id
https://cssrumapi.azurewebsites.net/Pictures/1

Pictures: get  all
https://cssrumapi.azurewebsites.net/Picturesall

Pictures: get all desc/Filter
https://cssrumapi.azurewebsites.net/Pictures/desc/Filter

Pictures: get all desc
https://cssrumapi.azurewebsites.net/Pictures/desc

## System

System: delete  all
https://cssrumapi.azurewebsites.net/Delete/all

System: delete  all Commands & Logs 
https://cssrumapi.azurewebsites.net/Delete/allCommands&Logs

System: delete  all EnvironmentalData& Pictures
https://cssrumapi.azurewebsites.net/Delete/allEnvironmentalData&Pictures




