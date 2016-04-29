using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using V8Net;

namespace HelloWorld
{
    class Program
    {
        static void Main(string[] args)
        {
            JavaScriptContextFactory.InitializeRuntime();
            var context = JavaScriptContextFactory.CreateContext();
        }
    }
}
