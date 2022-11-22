using Microsoft.EntityFrameworkCore;
using MinimalAPIPostgresSqlCSS.Models;


/*
 * CSSDb is a DBcontext that is used to create the db tables on the postgresql server
 * all the instance of models interfaces are create in the database. 
 * 
 * @author David G. Ortiz 
 * 
 */




namespace MinimalAPIPostgresSqlCSS.Data
{
    public class CSSDb :DbContext
    {
        public CSSDb(DbContextOptions<CSSDb>options) :base(options)
        {
            //This line give acces to change timezone on timestamps.From utc to others.
            AppContext.SetSwitch("Npgsql.EnableLegacyTimestampBehavior", true);
        }
        public DbSet<Admins> Admins => Set<Admins>();
        public DbSet<Commands> Commands => Set<Commands>();
        public DbSet<EnvironmentalData> EnvironmentalData => Set<EnvironmentalData>();
        public DbSet<Logs> Logs => Set<Logs>();
        public DbSet<Pictures> Pictures => Set<Pictures>();

        
    }
}





