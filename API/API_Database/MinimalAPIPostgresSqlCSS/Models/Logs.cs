using System.ComponentModel.DataAnnotations;

namespace MinimalAPIPostgresSqlCSS.Models
{
    public class Logs
    {
        [Key]
        public int Log_id { get; set; }
        public string? Log_text { get; set; }
        public DateTime Times_tamps { get; set; } = DateTime.UtcNow;
    }
}
 