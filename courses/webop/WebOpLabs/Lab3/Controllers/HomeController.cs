using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Domain;
using Lab3.Model;
namespace Lab3new.Controllers
{
    public class HomeController : Controller
    {
        IEnumerable<Bag> _bags;
        public HomeController(IEnumerable<Bag> bags){
            _bags = bags;
        }
        public IActionResult Index()
        {
            ViewData["MenuActive"] = "home";
            return View();
        }
        public IActionResult Bags(){
            List<BagModel> bags = new List<BagModel>();
            foreach(var bag in _bags)
            {
                bags.Add(new BagModel(bag));
            }

            ViewData["MenuActive"] = "bags";

            return View(new BagsModel() { Bags = bags});
        }

        public IActionResult Bag(int id)
        {
            if (id == 0)
                return RedirectToAction("Bags");
            var bag = _bags.FirstOrDefault(x => x.Id == id);
            if(bag == null)
                return RedirectToAction("Bags");

            return View(bag);
        }
    }
}
