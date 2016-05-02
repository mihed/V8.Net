using System;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using V8Net;

namespace V8.Net.Tests
{
    [TestClass]
    public class JavaScriptContextFactoryTest
    {

        [TestMethod]
        public void InitializeRuntime_InitializedRuntime_InitializedSet()
        {
            JavaScriptContextFactory.InitializeRuntime();
            Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
        }

        [TestMethod]
        public void InitializeRuntime_InitializedRuntimeMultipleThreads_InitializedSet()
        {
            for (var i = 0; i < 1000; i++)
                new Thread(() =>
                {
                    JavaScriptContextFactory.InitializeRuntime();
                    Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
                }).Start();
        }

        [TestMethod]
        public void InitializeRuntime_InitializedRuntimeThreadPool_InitializedSet()
        {
            Parallel.For(0, 1000, index =>
            {
                JavaScriptContextFactory.InitializeRuntime();
                Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
            });
        }

        [TestMethod]
        public void InitializeRuntime_InitializedRuntimeTwoTimes_NothingChanges()
        {
            JavaScriptContextFactory.InitializeRuntime();
            Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
            JavaScriptContextFactory.InitializeRuntime();
            Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
        }

        [TestMethod]
        public void CreateContext_SingleThread_Works()
        {
            JavaScriptContextFactory.InitializeRuntime();
            Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
            JavaScriptContextFactory.CreateContext().Dispose();
        }

        [TestMethod]
        public void CreateContext_MultipleThreads_Works()
        {
            JavaScriptContextFactory.InitializeRuntime();
            Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
            var threadCount = 100;
            var threads = new Thread[threadCount];
            for (var i = 0; i < threadCount; i++)
            {
                threads[i] = new Thread(() =>
                {
                    try
                    {
                        JavaScriptContextFactory.CreateContext().Dispose();
                    }
                    catch (Exception)
                    {
                        Assert.Fail("The context threw an exception");
                    }
                });
                threads[i].Start();
            }
            for (var i = 0; i < threadCount; i++)
                threads[i].Join();
        }

        [TestMethod]
        public void CreateContext_ThreadPool_Works()
        {
            JavaScriptContextFactory.InitializeRuntime();
            Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
            Parallel.For(0, 100, index => { JavaScriptContextFactory.CreateContext().Dispose(); });
        }
    }
}