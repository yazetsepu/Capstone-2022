using System.ComponentModel.DataAnnotations;

namespace MinimalAPIPostgresSqlCSS.Models
{
    public class Admins
    {
        [Key]
        public int User_Id { get; set; }
        public string? Admin_Email { get; set; }
        public string? Admin_Password { get; set; }

        //Foreign key connection.
       
        public ICollection<Commands>? Commands { get; set; }
    }
}
