using System.ComponentModel.DataAnnotations;

namespace MinimalAPIPostgresSqlCSS.Models
{
    public class Admins
    {
        [Key]
        public int User_Id { get; set; }
        public string? Admin_Email { get; set; }
        public string? Admin_Password { get; set; }
        public ICollection<Commands>? Commands { get; set; }
    }
}
