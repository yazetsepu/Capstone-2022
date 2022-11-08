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
                    Times_tamps = table.Column<string>(type: "text", nullable: true),
                    Log_text = table.Column<string>(type: "text", nullable: true)
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
                    Classification_id = table.Column<int>(type: "integer", nullable: false),
                    Classification_accurracy = table.Column<float>(type: "real", nullable: false),
                    Pic_Path = table.Column<string>(type: "text", nullable: true),
                    Clock = table.Column<string>(type: "text", nullable: true)
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
                    Command_received = table.Column<string>(type: "text", nullable: true),
                    Command_read = table.Column<string>(type: "text", nullable: true),
                    Command_performed = table.Column<string>(type: "text", nullable: true),
                    Duplicate_flag = table.Column<int>(type: "integer", nullable: true),
                    Command_string = table.Column<string>(type: "text", nullable: true),
                    Command_value = table.Column<string>(type: "text", nullable: true),
                    Logid = table.Column<int>(type: "integer", nullable: false),
                    LogsLog_id = table.Column<int>(type: "integer", nullable: true),
                    AdminsUser_Id = table.Column<int>(type: "integer", nullable: true)
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
                    Humidity = table.Column<float>(type: "real", nullable: false),
                    Times_tamps = table.Column<string>(type: "text", nullable: true),
                    PicturesId = table.Column<int>(type: "integer", nullable: true)
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
                column: "PicturesId",
                unique: true);
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
