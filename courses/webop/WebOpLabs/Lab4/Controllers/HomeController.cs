using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Domain;
using Lab3.Model;
using Lab4.Data;

namespace Lab3new.Controllers
{
    public class HomeController : Controller
    {
        private const int pageSize = 3;
        private readonly EfDbContext _context;
        public HomeController(EfDbContext context)
        {
            _context = context;
        }
        public IActionResult Index()
        {
            ViewData["MenuActive"] = "home";
            return View();
        }

        [HttpGet]
        public IActionResult Bags(int page)
        {
            if(page == 0)
                page = 1;
            int pageIndex = page - 1;
            List<BagModel> bags = new List<BagModel>();
            foreach(var bag in _context.Bags.Where(b => b.ImageLink != null).Skip(pageIndex * pageSize).Take(pageSize))
            {
                bags.Add(new BagModel(bag));
            }

            ViewData["MenuActive"] = "bags";
            ViewData["Pages"] = (int)Math.Ceiling(_context.Bags.Count(b => b.ImageLink != null)/(float)pageSize);
            ViewData["Page"] = page;
            return View(new BagsModel() { Bags = bags});
        }

        public IActionResult Bag(int id)
        {
            var bag = _context.Bags.FirstOrDefault(x => x.Id == id);
            if(bag == null)
                return RedirectToAction("Bags");

            return View(bag);
        }
    }
}
