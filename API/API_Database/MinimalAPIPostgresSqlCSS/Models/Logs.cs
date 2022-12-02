using MinimalAPIPostgresSqlCSS.Models;
using System.ComponentModel.DataAnnotations;

/*
 * Logs models interface, getters y setters, for columns on database.  
 * 
 * @author David G. Ortiz Velez
 * 
 */

namespace MinimalAPIPostgresSqlCSS.Models
{
    public class Logs
    {
        [Key]
        public int Log_Id { get; set; }
        public string? Log_Text { get; set; }

        //Cambiaste esto.
        public DateTime Timestamps { get; set; } = DateTime.UtcNow;
    }
}
 