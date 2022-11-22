using System.ComponentModel.DataAnnotations;



/*
 * Admins models interface, getters y setters, for columns on database. 
 * The ICollection of Commands because the relation with the table admins and commands is one to many.
 * An admin can have many commands. 
 * 
 * @author David G. Ortiz Velez
 */
namespace MinimalAPIPostgresSqlCSS.Models
{
    public class Admins
    {
        [Key]
        public int User_Id { get; set; }
        public string? Admin_Email { get; set; }
        public string? Admin_Password { get; set; }
        public virtual ICollection<Commands>? Commands { get; set; }
    }
}
