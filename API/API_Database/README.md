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
     Database=CSSDb;User 
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
![DBContext](https://user-images.githubusercontent.com/31049645/200149395-0beac508-3330-437d-bccc-a815427c65d8.png)


**Routes and API JSON examples:**

## Routes Admins:
Post: /admins/

![adminspostjson](https://user-images.githubusercontent.com/31049645/200149731-a87c32e4-ccbc-4039-92d9-378f265a0904.png)

Get: /admins/{id}

Put: /admins/{id}

![adminsputjson](https://user-images.githubusercontent.com/31049645/200149788-ae5ce2ac-3068-4f62-ad67-adfb6332beb7.png)

Delete: /admins/{id}

GET All: /adminsAll

## Routes Commands:
Post: /Commands/

![commandspostjson](https://user-images.githubusercontent.com/31049645/200149889-f37857b8-5407-451d-a08f-1fec611b9d58.png)

GET: /Commands/{id}

PUT:/Commands/{id}

![Commandsputjson](https://user-images.githubusercontent.com/31049645/200149950-3dffe87d-5060-44f5-a0d6-d337fc6756dd.png)

DELETE: /Commands/{id}

GET ALL: /CommandsAll

## Routes Enviromental Data:
POST: /EnvironmentalData/

![EnviromentalData Post](https://user-images.githubusercontent.com/31049645/200150021-4549689a-03f5-464d-9c2b-65c31deb7407.png)

GET: /EnvironmentalData/{id}

PUT: /EnvironmentalData/{id}

![image](https://user-images.githubusercontent.com/31049645/200150048-0d9e2759-7b59-4441-a2a8-f39f8afa1438.png)

DELETE: /EnvironmentalData/{id}

GET ALL: /EnvironmentalDataAll

## Routes Logs

POST: /Logs/

![Logs Post Json Example](https://user-images.githubusercontent.com/31049645/200150073-9a899a5d-cb78-44a3-8b66-41ca49bed463.png)

GET: /Logs/{id}

PUT: /Logs/{id}

![Logs put Json Example](https://user-images.githubusercontent.com/31049645/200150147-8783fd0c-a51a-4800-83d5-b92683230ed1.png)

DELETE: /Logs/{id}

GET ALL: /LogsAll 

## Routes Pictures:

POST: /Pictures/

![image](https://user-images.githubusercontent.com/31049645/200150181-413d7845-343a-4a74-9740-ff4d955933dd.png)

GET: /Picture/{id}

PUT: /Pictures/{id}

![image](https://user-images.githubusercontent.com/31049645/200150287-f23f810e-fc30-4a26-92b1-41d0b9d62726.png)

DELETE: /Pictures/{id}

GET ALL: /PicturesAll


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

