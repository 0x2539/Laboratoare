using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.Entity;

namespace Models
{
    public class PhotoDB
    {
        public int ID { get; set; }
        public string PhotoType { get; set; }
        public string Photo { get; set; }
        public string Category { get; set; }
        public string Description { get; set; }
        public int Album { get; set; }
        public int User { get; set; }

    }
    public class PhotoDBContext : DbContext
    {
        public DbSet<PhotoDB> Photos { get; set; }
    }
}