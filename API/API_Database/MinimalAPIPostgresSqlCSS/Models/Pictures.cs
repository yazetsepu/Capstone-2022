using Microsoft.AspNetCore.Authentication;
using Microsoft.EntityFrameworkCore.Metadata.Internal;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Runtime.CompilerServices;

namespace MinimalAPIPostgresSqlCSS.Models
{
    public class Pictures
    {
        [Key]
        public int Pic_Id { get; set; } 

        public int? Classification_id { get; set; }
        public int? Classification_id_2 { get; set; }
        public int? Classification_id_3 { get; set; }
        public int? Classification_id_4 { get; set; }

        public float? Classification_accurracy { get; set; }

        public float? Classification_accurracy_2 { get; set; }
        public float? Classification_accurracy_3 { get; set; }
        public float? Classification_accurracy_4 { get; set; }
        public string? Camera_Pic_Path_1 { get; set; }
        public string? Camera_Pic_Path_2 { get; set; }
        public string? Camera_Pic_Path_3 { get; set; }
        public string? Camera_Pic_Path_4 { get; set; }
        public DateTime Times_tamps { get; set; } = DateTime.UtcNow;


    }
}
