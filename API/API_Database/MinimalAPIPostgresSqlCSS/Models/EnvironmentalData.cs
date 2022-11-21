using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using Microsoft.EntityFrameworkCore.Metadata.Internal;
using System.Runtime.CompilerServices;
using Microsoft.AspNetCore.Authentication;
using System.Diagnostics.Metrics;

namespace MinimalAPIPostgresSqlCSS.Models
{
    public class EnvironmentalData
    {
        [Key]
        public int Entry_Id { get; set; }

        public float? Soil_moisture  { get; set; }

        public float? Soil_moisture_2 { get; set; }
        public float? Soil_moisture_3 { get; set; }
        public float? Soil_moisture_4 { get; set; }
        public float? Soil_moisture_5 { get; set; }
        public float? Soil_moisture_6 { get; set; }
        public float? Soil_moisture_7 { get; set; }
        public float? Soil_moisture_8 { get; set; }
        public float? Humidity { get; set; }
        public float? Light { get; set; }
       public string? Reservoir_water_level { get; set; }
        public int? PicturesId { get; set; } 
        public Pictures? Pictures { get; set; }
        public DateTime Times_tamps { get; set; } = DateTime.UtcNow;
    }
}
