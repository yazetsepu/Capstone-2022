using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace MinimalAPIPostgresSqlCSS.Migrations
{
    public partial class migrationtest1 : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<string>(
                name: "Reservoir_water_level",
                table: "EnvironmentalData",
                type: "text",
                nullable: true);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "Reservoir_water_level",
                table: "EnvironmentalData");
        }
    }
}
