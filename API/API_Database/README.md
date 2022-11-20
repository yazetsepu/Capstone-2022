
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


**Models:**
Admins: 

![Admin model example](https://user-images.githubusercontent.com/31049645/200149215-8b3c7ada-9fc9-459b-a803-062e67e8bbb8.png)

Commands:

![Commands model example](https://user-images.githubusercontent.com/31049645/200149295-bd0edbc7-5495-4be5-8e2a-566ccd47b327.png)

EnviromentalData:

![EnviromentalData model example](https://user-images.githubusercontent.com/31049645/200149298-7f4f86f2-1270-4600-8065-2cc88310de68.png)

Logs:

![Logs model example](https://user-images.githubusercontent.com/31049645/200149302-c0587caa-f03c-4f30-b850-0578adb91550.png)

Pictures:

![Picture model example](https://user-images.githubusercontent.com/31049645/200149303-c16aaad5-b7c9-4c82-9390-cd84aafa8bd5.png)


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

![image](https://user-images.githubusercontent.com/31049645/200150354-c63f4845-b1fb-43c4-9431-52ffca4a89d9.png)

Commands:

![image](https://user-images.githubusercontent.com/31049645/200150366-48e0cfcf-ef36-426e-9881-ac61efff9dc9.png)

EnvironmentalData:

![image](https://user-images.githubusercontent.com/31049645/200150375-98081aef-c8e7-4ab1-8c5b-482156ccb521.png)

Logs:

![image](https://user-images.githubusercontent.com/31049645/200150327-b4b2b055-fe28-42cb-820e-8deaa65416f9.png)

Pictures:

![image](https://user-images.githubusercontent.com/31049645/200150390-4d59b85a-1022-487e-9392-0c9fe726a7de.png)

# Routes:
## Admins
admins:Post/
https://cssrumapi.azurewebsites.net/admins
```json
{
  "command_Id": 0,
  "duplicate_flag": 0,
  "command_string": "string",
  "command_value": "string",
  "adminsUser_Id": 0,
  "admins": {
    "user_Id": 0,
    "admin_Email": "string",
    "admin_Password": "string",
    "commands": [
      "string"
    ]
  },
  "logid": 0,
  "logs": {
    "log_id": 0,
    "log_text": "string",
    "times_tamps": "2022-11-20T21:33:26.009Z"
  },
  "command_received": "2022-11-20T21:33:26.009Z",
  "command_read": "2022-11-20T21:33:26.009Z",
  "command_performed": "2022-11-20T21:33:26.009Z"
}
```

admins:get by id
https://cssrumapi.azurewebsites.net/admins/1

admins: put by id
https://cssrumapi.azurewebsites.net/admins/1
```json
{
  "command_Id": 0,
  "duplicate_flag": 0,
  "command_string": "string",
  "command_value": "string",
  "adminsUser_Id": 0,
  "admins": {
    "user_Id": 0,
    "admin_Email": "string",
    "admin_Password": "string",
    "commands": [
      "string"
    ]
  },
  "logid": 0,
  "logs": {
    "log_id": 0,
    "log_text": "string",
    "times_tamps": "2022-11-20T21:33:26.009Z"
  },
  "command_received": "2022-11-20T21:33:26.009Z",
  "command_read": "2022-11-20T21:33:26.009Z",
  "command_performed": "2022-11-20T21:33:26.009Z"
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
  "duplicate_flag": 0,
  "command_string": "string",
  "command_value": "string",
  "adminsUser_Id": 0,
  "admins": {
    "user_Id": 0,
    "admin_Email": "string",
    "admin_Password": "string",
    "commands": [
      "string"
    ]
  },
  "logid": 0,
  "logs": {
    "log_id": 0,
    "log_text": "string",
    "times_tamps": "2022-11-20T21:33:26.009Z"
  },
  "command_received": "2022-11-20T21:33:26.009Z",
  "command_read": "2022-11-20T21:33:26.009Z",
  "command_performed": "2022-11-20T21:33:26.009Z"
}
```
commands: get by id
https://cssrumapi.azurewebsites.net/commands/1

commands: put by commands
https://cssrumapi.azurewebsites.net/commands/1
```json
{
  "command_Id": 0,
  "duplicate_flag": 0,
  "command_string": "string",
  "command_value": "string",
  "adminsUser_Id": 0,
  "admins": {
    "user_Id": 0,
    "admin_Email": "string",
    "admin_Password": "string",
    "commands": [
      "string"
    ]
  },
  "logid": 0,
  "logs": {
    "log_id": 0,
    "log_text": "string",
    "times_tamps": "2022-11-20T21:33:26.009Z"
  },
  "command_received": "2022-11-20T21:33:26.009Z",
  "command_read": "2022-11-20T21:33:26.009Z",
  "command_performed": "2022-11-20T21:33:26.009Z"
}
```
commands: delete by id 
https://cssrumapi.azurewebsites.net/commands/1

commands: get all commands
https://cssrumapi.azurewebsites.net/commandsAll

commands: put commands_read by id
https://cssrumapi.azurewebsites.net/commands/Command_read/1
```json
{
//This have to be blank.
}
```

commands: put commands_performed by id
https://cssrumapi.azurewebsites.net/commands/Command_performed/1
```json
{
  //This have to be blank.
}
```
## EnvironmentalData

environmentaldata:Post
https://cssrumapi.azurewebsites.net/Environmentaldata
```json
{
  "entry_Id": 0,
  "water_level": 0,
  "temperature": 0,
  "soil_moisture": 0,
  "soil_moisture_2": 0,
  "soil_moisture_3": 0,
  "soil_moisture_4": 0,
  "soil_moisture_5": 0,
  "soil_moisture_6": 0,
  "soil_moisture_7": 0,
  "soil_moisture_8": 0,
  "humidity": 0,
  "light": 0,
  "reservoir_water_level": "string",
  "picturesId": 0,
  "pictures": {
    "pic_Id": 0,
    "classification_id": 0,
    "classification_id_2": 0,
    "classification_id_3": 0,
    "classification_id_4": 0,
    "classification_accurracy": 0,
    "classification_accurracy_2": 0,
    "classification_accurracy_3": 0,
    "classification_accurracy_4": 0,
    "camera_Pic_Path_1": "string",
    "camera_Pic_Path_2": "string",
    "camera_Pic_Path_3": "string",
    "camera_Pic_Path_4": "string",
    "times_tamps": "2022-11-20T21:43:24.301Z"
  },
  "times_tamps": "2022-11-20T21:43:24.301Z"
}

```

environmentaldata:Get by id
https://cssrumapi.azurewebsites.net/environmentaldata/1

environmentaldata:Put by id
https://cssrumapi.azurewebsites.net/environmentaldata/1
```json
{
  "entry_Id": 0,
  "water_level": 0,
  "temperature": 0,
  "soil_moisture": 0,
  "soil_moisture_2": 0,
  "soil_moisture_3": 0,
  "soil_moisture_4": 0,
  "soil_moisture_5": 0,
  "soil_moisture_6": 0,
  "soil_moisture_7": 0,
  "soil_moisture_8": 0,
  "humidity": 0,
  "light": 0,
  "reservoir_water_level": "string",
  "picturesId": 0,
  "pictures": {
    "pic_Id": 0,
    "classification_id": 0,
    "classification_id_2": 0,
    "classification_id_3": 0,
    "classification_id_4": 0,
    "classification_accurracy": 0,
    "classification_accurracy_2": 0,
    "classification_accurracy_3": 0,
    "classification_accurracy_4": 0,
    "camera_Pic_Path_1": "string",
    "camera_Pic_Path_2": "string",
    "camera_Pic_Path_3": "string",
    "camera_Pic_Path_4": "string",
    "times_tamps": "2022-11-20T21:43:24.301Z"
  },
  "times_tamps": "2022-11-20T21:43:24.301Z"
}

```

environmentaldata:delete by id
https://cssrumapi.azurewebsites.net/environmentaldata/1

environmentaldata: get all with classid
https://cssrumapi.azurewebsites.net/environmentaldata/classid

environmentaldata: get all 
https://cssrumapi.azurewebsites.net/environmentaldataall

## Logs
logs:post
https://cssrumapi.azurewebsites.net/Logs
```json
{
  "log_id": 0,
  "log_text": "string",
  "times_tamps": "2022-11-20T21:44:42.807Z"
}
```
logs: get  by id
https://cssrumapi.azurewebsites.net/logs/1

logs: put  by id
https://cssrumapi.azurewebsites.net/logs/1
```json
{
  "log_id": 0,
  "log_text": "string",
  "times_tamps": "2022-11-20T21:44:42.807Z"
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
  "classification_id": 0,
  "classification_id_2": 0,
  "classification_id_3": 0,
  "classification_id_4": 0,
  "classification_accurracy": 0,
  "classification_accurracy_2": 0,
  "classification_accurracy_3": 0,
  "classification_accurracy_4": 0,
  "camera_Pic_Path_1": "string",
  "camera_Pic_Path_2": "string",
  "camera_Pic_Path_3": "string",
  "camera_Pic_Path_4": "string",
  "times_tamps": "2022-11-20T21:44:56.590Z"
}
```
Pictures: get  by id
https://cssrumapi.azurewebsites.net/Pictures/1

Pictures: put  by id
https://cssrumapi.azurewebsites.net/Pictures/1
```json
{
  "pic_Id": 0,
  "classification_id": 0,
  "classification_id_2": 0,
  "classification_id_3": 0,
  "classification_id_4": 0,
  "classification_accurracy": 0,
  "classification_accurracy_2": 0,
  "classification_accurracy_3": 0,
  "classification_accurracy_4": 0,
  "camera_Pic_Path_1": "string",
  "camera_Pic_Path_2": "string",
  "camera_Pic_Path_3": "string",
  "camera_Pic_Path_4": "string",
  "times_tamps": "2022-11-20T21:44:56.590Z"
}
```
Pictures: delete  by id
https://cssrumapi.azurewebsites.net/Pictures/1

Pictures: get  all
https://cssrumapi.azurewebsites.net/Picturesall

Pictures: get all desc
https://cssrumapi.azurewebsites.net/Pictures/desc

