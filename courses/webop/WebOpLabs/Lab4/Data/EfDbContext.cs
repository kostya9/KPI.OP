using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Domain;
using Microsoft.EntityFrameworkCore;

namespace Lab4.Data
{
    public class EfDbContext : DbContext
    {
        public DbSet<Bag> Bags { get; set; }

        public EfDbContext(DbContextOptions options) : base(options)
        {
            
        }

        protected override void OnModelCreating(ModelBuilder builder)
        {
            builder.Entity<Bag>().ToTable("Bags").HasKey(b => b.Id);
        }
    }
}
