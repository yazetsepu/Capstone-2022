using Microsoft.AspNetCore.Authentication;
using Microsoft.EntityFrameworkCore.Metadata.Internal;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace MinimalAPIPostgresSqlCSS.Models
{
    public class Pictures
    {
        [Key]
        public int Pic_Id { get; set; } 

        public int Classification_id { get; set; }  

        public float Classification_accurracy { get; set; }
    
       
        public string? Pic_Path { get; set; }

        public string? Clock { get; set; }

        //This is for foreign Key connection with the enviromental table.
        //One to one
        public  EnvironmentalData? EnvironmentalData { get; set; }   
    }
}
