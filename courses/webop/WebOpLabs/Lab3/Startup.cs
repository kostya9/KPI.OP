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
            services.AddSingleton<IEnumerable<Bag>>(new List<Bag>{
                {new Bag(){
                    Name = "a", 
                    ImageLink = "https://media.gucci.com/style/DarkGray_South_0_160_316x316/1449741628/421890_A7M0T_6339_001_090_0000_Light-GG-Marmont-leather-top-handle-bag.jpg",
                }},
                {new Bag()
                {
                    Name = "aa",
                    ImageLink = "http://bagbible.com/blog/wp-content/uploads/2009/04/duffell_bag.jpg"
                }},
                {new Bag(){
                    Name = "aaa",
                    ImageLink = "https://s-media-cache-ak0.pinimg.com/originals/c7/c3/ea/c7c3ead2a778f8a4f4f0523a15f3a427.jpg"
                }},
                {new Bag(){
                    Name = "aaaa",
                    ImageLink = "https://ae01.alicdn.com/kf/HTB1ftSYIpXXXXXVXVXXq6xXFXXXD/HETI-2015-Hot-men-and-women-printing-leaves-backpacks-mochila-rucksack-fashion-canvas-bags-retro-casual.jpg_350x350.jpg"
                }},
                {new Bag{
                    Name = "aaaaa",
                    ImageLink = "http://shop.millscanvas.com/media/images/naptholred_ice_bag.jpg"
                }},
                {new Bag{
                    Id = 10,
                    Name = "Reusable Shopping Bag",
                    Description = "Use this bag a lot of times! If you are a great mathematician count your income from not buying bags. You will be suprised!",
                    ImageLink = "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSUZg64JyyVFS4Cx340G2Qd_zddEFbQbPCO76N4uHL10Cy7gH-sKw"
                }}
            });
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
