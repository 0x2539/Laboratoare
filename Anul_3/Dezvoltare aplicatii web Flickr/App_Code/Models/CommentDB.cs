using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.Entity;

namespace Models
{
    public class CommentDB
    {
        public int ID { get; set; }
        public string Text { get; set; }
        public int Photo { get; set; }
        public int User { get; set; }

    }
    public class CommentDBContext : DbContext
    {
        public DbSet<CommentDB> Comments { get; set; }
    }
}