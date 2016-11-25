using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using Domain;
using Lab4.Data;
using Microsoft.EntityFrameworkCore;

namespace Lab3new
{
    public class Startup
    {
        public Startup(IHostingEnvironment env)
        {
            var builder = new ConfigurationBuilder()
                .SetBasePath(env.ContentRootPath)
                .AddJsonFile("appsettings.json", optional: true, reloadOnChange: true)
                .AddJsonFile($"appsettings.{env.EnvironmentName}.json", optional: true)
                .AddEnvironmentVariables();
            Configuration = builder.Build();
        }

        public IConfigurationRoot Configuration { get; }

        // This method gets called by the runtime. Use this method to add services to the container.
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddEntityFrameworkSqlServer()
                    .AddDbContext<EfDbContext>((provider, options) =>
                         options.UseSqlServer(Configuration.GetValue<string>("ConnectionStringLocal"),
                                                b => b.MigrationsAssembly("Lab4"))
                         .UseInternalServiceProvider(provider));
            services.AddSingleton<IEnumerable<Bag>>(Bag.GetInitializedBags());
            // Add framework services.
            services.AddMvc();

            
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IHostingEnvironment env, ILoggerFactory loggerFactory)
        {
            loggerFactory.AddConsole(Configuration.GetSection("Logging"));
            loggerFactory.AddDebug();

            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
                app.UseBrowserLink();
            }
            else
            {
                app.UseExceptionHandler("/Home/Error");
            }
            var context = app.ApplicationServices.GetService<EfDbContext>();

            if (!context.Bags.Any())
            {
                var bags = Bag.GetInitializedBags();
                foreach (var bag in bags)
                {
                    bag.Id = 0;
                    context.Add(bag);
                }
                context.SaveChanges();
            }

            app.UseStaticFiles();

            app.UseMvc(routes =>
            {
                routes.MapRoute(
                    name:"bag",
                    template:"Bags/{id}",
                    defaults: new {controller="Home", action="Bag"}
                    );
                routes.MapRoute(
                    name: "default",
                    template: "{controller=Home}/{action=Index}/{id?}");

            });
        }
    }
}
