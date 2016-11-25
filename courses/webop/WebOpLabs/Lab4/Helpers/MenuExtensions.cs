using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.AspNetCore.Html;

namespace Lab3.Helpers{
    public static class MenuExtensions{
        static readonly string activeClassName = "active";
        public static HtmlString GetMenuItemClass(this IHtmlHelper helper, string name)
        {
            var realName = helper.ViewData["MenuActive"];

            if(realName == null)
                return new HtmlString("");
            
            return new HtmlString(realName.Equals(name) ? activeClassName : "");
            

        }
    }
}