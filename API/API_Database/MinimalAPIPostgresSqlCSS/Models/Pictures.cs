using Microsoft.AspNetCore.Authentication;
using Microsoft.EntityFrameworkCore.Metadata.Internal;
using MinimalAPIPostgresSqlCSS.Models;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Runtime.CompilerServices;

/*
 * Pictures models interface, getters y setters, for columns on database.  
 * 
 * @author David G. Ortiz Velez
 */

namespace MinimalAPIPostgresSqlCSS.Models
{
    public class Pictures
    {
        [Key]
        public int Pic_Id { get; set; } 
        public int? Classification_Id_1 { get; set; }
        public int? Classification_Id_2 { get; set; }
        public int? Classification_Id_3 { get; set; }
        public int? Classification_Id_4 { get; set; }
        public float? Classification_Accurracy_1 { get; set; }
        public float? Classification_Accurracy_2 { get; set; }
        public float? Classification_Accurracy_3 { get; set; }
        public float? Classification_Accurracy_4 { get; set; }
        public string? Camera_Pic_Path_1 { get; set; }
        public string? Camera_Pic_Path_2 { get; set; }
        public string? Camera_Pic_Path_3 { get; set; }
        public string? Camera_Pic_Path_4 { get; set; }

        public DateTime Timestamps { get; set; } = DateTime.Now;


    }
}
