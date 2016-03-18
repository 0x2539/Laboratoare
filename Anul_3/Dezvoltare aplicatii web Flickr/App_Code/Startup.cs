using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(Dezvoltare_aplicatii_web_Flickr.Startup))]
namespace Dezvoltare_aplicatii_web_Flickr
{
    public partial class Startup {
        public void Configuration(IAppBuilder app) {
            ConfigureAuth(app);
        }
    }
}
