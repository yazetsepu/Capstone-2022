using Microsoft.EntityFrameworkCore;
using MinimalAPIPostgresSqlCSS.Models;

namespace MinimalAPIPostgresSqlCSS.Data
{
    public class CSSDb :DbContext
    {
        public CSSDb(DbContextOptions<CSSDb>options) :base(options)
        {

        }
        public DbSet<Admins> Admins => Set<Admins>();
        public DbSet<Commands> Commands => Set<Commands>();
        public DbSet<EnvironmentalData> EnvironmentalData => Set<EnvironmentalData>();
        public DbSet<Logs> Logs => Set<Logs>();
        public DbSet<Pictures> Pictures => Set<Pictures>();

        
    }
}
