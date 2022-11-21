using System;
using Microsoft.EntityFrameworkCore.Migrations;
using Npgsql.EntityFrameworkCore.PostgreSQL.Metadata;

#nullable disable

namespace MinimalAPIPostgresSqlCSS.Migrations
{
    public partial class migrationtest : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Admins",
                columns: table => new
                {
                    User_Id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    Admin_Email = table.Column<string>(type: "text", nullable: true),
                    Admin_Password = table.Column<string>(type: "text", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Admins", x => x.User_Id);
                });

            migrationBuilder.CreateTable(
                name: "Logs",
                columns: table => new
                {
                    Log_Id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    Log_Text = table.Column<string>(type: "text", nullable: true),
                    Timestamps = table.Column<DateTime>(type: "timestamp without time zone", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Logs", x => x.Log_Id);
                });

            migrationBuilder.CreateTable(
                name: "Pictures",
                columns: table => new
                {
                    Pic_Id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    Classification_Id_1 = table.Column<int>(type: "integer", nullable: true),
                    Classification_Id_2 = table.Column<int>(type: "integer", nullable: true),
                    Classification_Id_3 = table.Column<int>(type: "integer", nullable: true),
                    Classification_Id_4 = table.Column<int>(type: "integer", nullable: true),
                    Classification_Accurracy_1 = table.Column<float>(type: "real", nullable: true),
                    Classification_Accurracy_2 = table.Column<float>(type: "real", nullable: true),
                    Classification_Accurracy_3 = table.Column<float>(type: "real", nullable: true),
                    Classification_Accurracy_4 = table.Column<float>(type: "real", nullable: true),
                    Camera_Pic_Path_1 = table.Column<string>(type: "text", nullable: true),
                    Camera_Pic_Path_2 = table.Column<string>(type: "text", nullable: true),
                    Camera_Pic_Path_3 = table.Column<string>(type: "text", nullable: true),
                    Camera_Pic_Path_4 = table.Column<string>(type: "text", nullable: true),
                    Timestamps = table.Column<DateTime>(type: "timestamp without time zone", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Pictures", x => x.Pic_Id);
                });

            migrationBuilder.CreateTable(
                name: "Commands",
                columns: table => new
                {
                    Command_Id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    Log_Id = table.Column<int>(type: "integer", nullable: true),
                    AdminsUser_Id = table.Column<int>(type: "integer", nullable: true),
                    Duplicate_Flag = table.Column<int>(type: "integer", nullable: true),
                    Command_String = table.Column<string>(type: "text", nullable: true),
                    Command_Value = table.Column<string>(type: "text", nullable: true),
                    Command_Received = table.Column<DateTime>(type: "timestamp without time zone", nullable: false),
                    Command_Read = table.Column<DateTime>(type: "timestamp without time zone", nullable: true),
                    Command_Performed = table.Column<DateTime>(type: "timestamp without time zone", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Commands", x => x.Command_Id);
                    table.ForeignKey(
                        name: "FK_Commands_Admins_AdminsUser_Id",
                        column: x => x.AdminsUser_Id,
                        principalTable: "Admins",
                        principalColumn: "User_Id");
                    table.ForeignKey(
                        name: "FK_Commands_Logs_Log_Id",
                        column: x => x.Log_Id,
                        principalTable: "Logs",
                        principalColumn: "Log_Id");
                });

            migrationBuilder.CreateTable(
                name: "EnvironmentalData",
                columns: table => new
                {
                    Entry_Id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    Pictures_Id = table.Column<int>(type: "integer", nullable: true),
                    Water_Level = table.Column<float>(type: "real", nullable: true),
                    Temperature = table.Column<float>(type: "real", nullable: true),
                    Soil_Moisture_1 = table.Column<float>(type: "real", nullable: true),
                    Soil_Moisture_2 = table.Column<float>(type: "real", nullable: true),
                    Soil_Moisture_3 = table.Column<float>(type: "real", nullable: true),
                    Soil_Moisture_4 = table.Column<float>(type: "real", nullable: true),
                    Soil_Moisture_5 = table.Column<float>(type: "real", nullable: true),
                    Soil_Moisture_6 = table.Column<float>(type: "real", nullable: true),
                    Soil_Moisture_7 = table.Column<float>(type: "real", nullable: true),
                    Soil_Moisture_8 = table.Column<float>(type: "real", nullable: true),
                    Humidity = table.Column<float>(type: "real", nullable: true),
                    Light = table.Column<float>(type: "real", nullable: true),
                    Reservoir_Water_Level = table.Column<string>(type: "text", nullable: true),
                    Timestamps = table.Column<DateTime>(type: "timestamp without time zone", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EnvironmentalData", x => x.Entry_Id);
                    table.ForeignKey(
                        name: "FK_EnvironmentalData_Pictures_Pictures_Id",
                        column: x => x.Pictures_Id,
                        principalTable: "Pictures",
                        principalColumn: "Pic_Id");
                });

            migrationBuilder.CreateIndex(
                name: "IX_Commands_AdminsUser_Id",
                table: "Commands",
                column: "AdminsUser_Id");

            migrationBuilder.CreateIndex(
                name: "IX_Commands_Log_Id",
                table: "Commands",
                column: "Log_Id");

            migrationBuilder.CreateIndex(
                name: "IX_EnvironmentalData_Pictures_Id",
                table: "EnvironmentalData",
                column: "Pictures_Id");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Commands");

            migrationBuilder.DropTable(
                name: "EnvironmentalData");

            migrationBuilder.DropTable(
                name: "Admins");

            migrationBuilder.DropTable(
                name: "Logs");

            migrationBuilder.DropTable(
                name: "Pictures");
        }
    }
}
