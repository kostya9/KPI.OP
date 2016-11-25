using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;
using Lab4.Data;

namespace Lab4.Migrations
{
    [DbContext(typeof(EfDbContext))]
    partial class EfDbContextModelSnapshot : ModelSnapshot
    {
        protected override void BuildModel(ModelBuilder modelBuilder)
        {
            modelBuilder
                .HasAnnotation("ProductVersion", "1.1.0-rtm-22752")
                .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

            modelBuilder.Entity("Domain.Bag", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd();

                    b.Property<string>("Description");

                    b.Property<string>("Factory");

                    b.Property<string>("ImageLink");

                    b.Property<string>("Name");

                    b.Property<string>("Owner");

                    b.Property<int>("Price");

                    b.Property<DateTime?>("TimeBought");

                    b.Property<DateTime>("TimeCreation");

                    b.HasKey("Id");

                    b.ToTable("Bags");
                });
        }
    }
}
