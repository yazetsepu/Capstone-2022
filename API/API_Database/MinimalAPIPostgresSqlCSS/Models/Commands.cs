using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.Design;
using MinimalAPIPostgresSqlCSS.Models;


namespace MinimalAPIPostgresSqlCSS.Models
{
    public class Commands //This is the model for de Commands table, for the DBcontex to create the database Entity framework design.


    {
        [Key]
        public int Command_Id { get; set; } //Command_Id is the id that identify this command.

        public int? Duplicate_flag { get; set; } //This determines if the command was receive more than one time and the arduino does not execute twice, and ignore them.

        public string? Command_string { get; set; } //Command name execute.


        //Foreign Key for Standard for Admins 
        public int? AdminsUser_Id { get; set; } //This is the  admin id that performe this command.
        public Admins? Admins { get; set; }  //Admin instance of the table Logs.
      
        public int? Logid { get; set; } //Log id that is created as the command is perform.
        public Logs? Logs { get; set; } //Log instance of the table Logs.

        public DateTime Command_received { get; set; } = DateTime.UtcNow; //This is the time that the command was posted.

        public DateTime? Command_read { get; set; } = DateTime.UtcNow; //This is the time that the command is read by the arduino.

        public DateTime? Command_performed { get; set; } = DateTime.UtcNow; //This is the time that the command is performed.
    }
}
