using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using Microsoft.EntityFrameworkCore.Metadata.Internal;
using System.Runtime.CompilerServices;
using Microsoft.AspNetCore.Authentication;
using System.Diagnostics.Metrics;

/*
 * Environmentaldata models interface, getters y setters, for columns on database. 
 * The foreingkey of picture instance and the object instance of pictures relation is one to one. 
 * 
 * @author David G. Ortiz Velez
 */

namespace MinimalAPIPostgresSqlCSS.Models
{
    public class EnvironmentalData
    {
        [Key]
        public int Entry_Id { get; set; }

        [ForeignKey("Pictures")]
        public int? Pictures_Id { get; set; }

        public float? Water_Level { get; set; }      
        public float? Temperature { get; set; }  
        public float? Soil_Moisture_1  { get; set; }
        public float? Soil_Moisture_2 { get; set; }
        public float? Soil_Moisture_3 { get; set; }
        public float? Soil_Moisture_4 { get; set; }
        public float? Soil_Moisture_5 { get; set; }
        public float? Soil_Moisture_6 { get; set; }
        public float? Soil_Moisture_7 { get; set; }
        public float? Soil_Moisture_8 { get; set; }
        public float? Humidity { get; set; }
        public float? Light { get; set; }
        public string? Reservoir_Water_Level { get; set; }
  

        public virtual Pictures? Pictures { get; set; }
        public DateTime Timestamps { get; set; } = DateTime.Now;
    }
}
