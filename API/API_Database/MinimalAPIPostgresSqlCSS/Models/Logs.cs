using System.ComponentModel.DataAnnotations;

namespace MinimalAPIPostgresSqlCSS.Models
{
    public class Logs
    {
        [Key]
        public int Log_Id { get; set; }
        public string? Log_Text { get; set; }
        public DateTime Timestamps { get; set; } = DateTime.UtcNow;
    }
}
 