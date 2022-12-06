using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.Design;
using MinimalAPIPostgresSqlCSS.Models;

/*
 * Commands models interface, getters y setters, for columns on database. 
 * The virtual logs instance and admins instance, also the creation of foreignkey.
 * Because the relation one to many with the admins and logs with a relation one to one. 
 * 
 * @author David G. Ortiz Velez
 */

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
        public DateTimeOffset Command_Received { get; set; } = DateTimeOffset.Now;
        public DateTimeOffset? Command_Read { get; set; } = DateTimeOffset.Now;
        public DateTimeOffset? Command_Performed { get; set; } = DateTimeOffset.Now;
    }
}
