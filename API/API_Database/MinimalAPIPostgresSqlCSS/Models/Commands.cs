using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.Design;
using MinimalAPIPostgresSqlCSS.Models;


namespace MinimalAPIPostgresSqlCSS.Models
{
    public class Commands 
    {
        [Key]
        public int Command_Id { get; set; }

        [ForeignKey("Logs")]
        public int? Log_Id { get; set; }

        [ForeignKey("Admins")]
        public int? AdminsUser_Id { get; set; }


        public int? Duplicate_Flag { get; set; } 
        public string? Command_String { get; set; }
        public string? Command_Value  { get; set; }

        public virtual Admins? Admins { get; set; }  
        public virtual Logs? Logs { get; set; } 
        public DateTime Command_Received { get; set; } = DateTime.UtcNow; 
        public DateTime? Command_Read { get; set; } = DateTime.UtcNow; 
        public DateTime? Command_Performed { get; set; } = DateTime.UtcNow; 
    }
}
