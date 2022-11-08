using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Diagnostics.Contracts;

namespace MinimalAPIPostgresSqlCSS.Models
{
    public class EnvironmentalData
    {
        [Key]
        public int? Entry_Id { get; set; }

        public float? Water_level { get; set; }      

        public float? Temperature { get; set; }  

        public float? Soil_moisture  { get; set; } 
        
        public float Humidity { get; set; }

       
        public string? Times_tamps { get; set; }

        //The atribute can be applied to the navigation
        //property and the related foreign key property.

        public int? PicturesId { get; set; } 
        public Pictures? Pictures { get; set; }   


    }
}
