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
                    Log_id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    Log_text = table.Column<string>(type: "text", nullable: true),
                    Times_tamps = table.Column<DateTime>(type: "timestamp without time zone", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Logs", x => x.Log_id);
                });

            migrationBuilder.CreateTable(
                name: "Pictures",
                columns: table => new
                {
                    Pic_Id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    Classification_id = table.Column<int>(type: "integer", nullable: true),
                    Classification_id_2 = table.Column<int>(type: "integer", nullable: true),
                    Classification_id_3 = table.Column<int>(type: "integer", nullable: true),
                    Classification_id_4 = table.Column<int>(type: "integer", nullable: true),
                    Classification_accurracy = table.Column<float>(type: "real", nullable: true),
                    Classification_accurracy_2 = table.Column<float>(type: "real", nullable: true),
                    Classification_accurracy_3 = table.Column<float>(type: "real", nullable: true),
                    Classification_accurracy_4 = table.Column<float>(type: "real", nullable: true),
                    Camera_Pic_Path_1 = table.Column<string>(type: "text", nullable: true),
                    Camera_Pic_Path_2 = table.Column<string>(type: "text", nullable: true),
                    Camera_Pic_Path_3 = table.Column<string>(type: "text", nullable: true),
                    Camera_Pic_Path_4 = table.Column<string>(type: "text", nullable: true),
                    Times_tamps = table.Column<DateTime>(type: "timestamp without time zone", nullable: false)
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
                    Duplicate_flag = table.Column<int>(type: "integer", nullable: true),
                    Command_string = table.Column<string>(type: "text", nullable: true),
                    Command_value = table.Column<string>(type: "text", nullable: true),
                    AdminsUser_Id = table.Column<int>(type: "integer", nullable: true),
                    Logid = table.Column<int>(type: "integer", nullable: true),
                    LogsLog_id = table.Column<int>(type: "integer", nullable: true),
                    Command_received = table.Column<DateTime>(type: "timestamp without time zone", nullable: false),
                    Command_read = table.Column<DateTime>(type: "timestamp without time zone", nullable: true),
                    Command_performed = table.Column<DateTime>(type: "timestamp without time zone", nullable: true)
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
                        name: "FK_Commands_Logs_LogsLog_id",
                        column: x => x.LogsLog_id,
                        principalTable: "Logs",
                        principalColumn: "Log_id");
                });

            migrationBuilder.CreateTable(
                name: "EnvironmentalData",
                columns: table => new
                {
                    Entry_Id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    Water_level = table.Column<float>(type: "real", nullable: true),
                    Temperature = table.Column<float>(type: "real", nullable: true),
                    Soil_moisture = table.Column<float>(type: "real", nullable: true),
                    Soil_moisture_2 = table.Column<float>(type: "real", nullable: true),
                    Soil_moisture_3 = table.Column<float>(type: "real", nullable: true),
                    Soil_moisture_4 = table.Column<float>(type: "real", nullable: true),
                    Soil_moisture_5 = table.Column<float>(type: "real", nullable: true),
                    Soil_moisture_6 = table.Column<float>(type: "real", nullable: true),
                    Soil_moisture_7 = table.Column<float>(type: "real", nullable: true),
                    Soil_moisture_8 = table.Column<float>(type: "real", nullable: true),
                    Humidity = table.Column<float>(type: "real", nullable: true),
                    Light = table.Column<float>(type: "real", nullable: true),
                    PicturesId = table.Column<int>(type: "integer", nullable: true),
                    Times_tamps = table.Column<DateTime>(type: "timestamp without time zone", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EnvironmentalData", x => x.Entry_Id);
                    table.ForeignKey(
                        name: "FK_EnvironmentalData_Pictures_PicturesId",
                        column: x => x.PicturesId,
                        principalTable: "Pictures",
                        principalColumn: "Pic_Id");
                });

            migrationBuilder.CreateIndex(
                name: "IX_Commands_AdminsUser_Id",
                table: "Commands",
                column: "AdminsUser_Id");

            migrationBuilder.CreateIndex(
                name: "IX_Commands_LogsLog_id",
                table: "Commands",
                column: "LogsLog_id");

            migrationBuilder.CreateIndex(
                name: "IX_EnvironmentalData_PicturesId",
                table: "EnvironmentalData",
                column: "PicturesId");
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
