
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
![image](https://user-images.githubusercontent.com/31049645/202928286-cd3f7819-103d-4c2d-9410-4fe295148e94.png)

Commands:
![image](https://user-images.githubusercontent.com/31049645/202928394-79d808c4-6fcd-4102-8ad9-b1a6f58fc94a.png)

EnvironmentalData:

![image](https://user-images.githubusercontent.com/31049645/202928353-bf87ac09-7e76-4c83-9665-3c5efeee1c53.png)

Logs:

![image](https://user-images.githubusercontent.com/31049645/202928370-6f1260a0-5193-4f3e-bc7a-e88e14d6b715.png)

Pictures:

![image](https://user-images.githubusercontent.com/31049645/202928379-75557947-2232-4568-a2e9-f2b72c447d24.png)

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

