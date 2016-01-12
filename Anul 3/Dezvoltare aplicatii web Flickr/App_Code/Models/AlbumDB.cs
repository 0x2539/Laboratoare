using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.Entity;

namespace Models
{
    public class AlbumDB
    {
        public int ID { get; set; }
        public string Name { get; set; }
        public int User { get; set; }

    }
    public class AlbumDBContext : DbContext
    {
        public DbSet<AlbumDB> Albums { get; set; }
    }
}