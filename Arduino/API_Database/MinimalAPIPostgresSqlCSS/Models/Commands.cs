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

        
        public string? Command_received { get; set; }

       
        public string? Command_read { get; set; }

       
        public string? Command_performed { get; set; }

        public int? Duplicate_flag { get; set; }

        public string? Command_string { get; set; }

        public string? Command_value  { get; set; }

        //Foreign Key for Standard for Admins 
      
        public int Logid { get; set; }
        public Logs? Logs { get; set; }

      
    }
}
