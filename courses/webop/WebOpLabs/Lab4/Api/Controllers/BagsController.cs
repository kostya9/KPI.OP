using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Domain;
using Lab4.Data;
using Microsoft.AspNetCore.Mvc;

// For more information on enabling Web API for empty projects, visit http://go.microsoft.com/fwlink/?LinkID=397860

namespace Lab4.Api.Controllers
{
    [Route("api/[controller]")]
    public class BagsController : Controller
    {
        private readonly EfDbContext _context;

        public BagsController(EfDbContext context)
        {
            _context = context;
        }
        // GET: api/values
        [HttpGet]
        public IEnumerable<Bag> Get()
        {
            return _context.Bags.ToList();
        }

        // GET api/values/5
        [HttpGet("{id}")]
        public Bag Bag(int id)
        {
            var bag = _context.Bags.FirstOrDefault(b => b.Id == id);
            if (bag == null)
            {
                this.Response.StatusCode = 404;
                return null;
            }

            return bag;
        }

        // POST api/values
        [HttpPost]
        public void Post([FromBody]Bag bag)
        {
            bag.Id = 0;
            this._context.Bags.Add(bag);
            _context.SaveChanges();
        }

        // PUT api/values/5
        [HttpPut("{id}")]
        public void Put(int id, [FromBody]Bag bag)
        {
            var foundBag = _context.Bags.FirstOrDefault(b => b.Id == id);

            if (foundBag == null || bag == null)
            {
                this.Response.StatusCode = 404;
                return;
            }

            foundBag.Name = bag.Name;
            foundBag.Description = foundBag.Description;
            foundBag.Price = foundBag.Price;

            _context.SaveChanges();
        }

        // DELETE api/values/5
        [HttpDelete("{id}")]
        public void Delete(int id)
        {
            var foundBag = _context.Bags.FirstOrDefault(b => b.Id == id);

            if (foundBag == null)
            {
                this.Response.StatusCode = 404;
                return;
            }

            _context.Bags.Remove(foundBag);
            _context.SaveChanges();
        }
    }
}

