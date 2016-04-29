using System.Threading;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using V8Net;

namespace V8.Net.Tests
{
    [TestClass]
    public class JavaScriptContextFactoryTest
    {
        [TestInitialize]
        public void Setup()
        {
            JavaScriptContextFactory.DestroyRuntime();
        }

        [TestMethod]
        public void InitializeRuntime_NonInitializedRuntime_InitializedSet()
        {
            JavaScriptContextFactory.InitializeRuntime();
            Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
        }

        [TestMethod]
        public void InitializeRuntime_NonInitializedRuntimeMultipleThreads_InitializedSet()
        {
            for (var i = 0; i < 1000; i++)
                new Thread(() =>
                {
                    JavaScriptContextFactory.InitializeRuntime();
                    Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
                }).Start();
        }

        [TestMethod]
        public void InitializeRuntime_NonInitializedRuntimeThreadPool_InitializedSet()
        {
            Parallel.For(0, 1000, index =>
            {
                JavaScriptContextFactory.InitializeRuntime();
                Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
            });
        }

        [TestMethod]
        public void InitializeRuntime_InitializedRuntime_NothingChanges()
        {
            JavaScriptContextFactory.InitializeRuntime();
            JavaScriptContextFactory.InitializeRuntime();
            Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
        }

        [TestMethod]
        public void InitializeRuntime_InitializedRuntimeMultipleThreads_NothingChanges()
        {
            JavaScriptContextFactory.InitializeRuntime();
            for (var i = 0; i < 1000; i++)
                new Thread(() =>
                {
                    JavaScriptContextFactory.InitializeRuntime();
                    Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
                }).Start();
        }

        [TestMethod]
        public void InitializeRuntime_InitializedRuntimeThreadPool_NothingChanges()
        {
            JavaScriptContextFactory.InitializeRuntime();
            Parallel.For(0, 1000, index =>
            {
                JavaScriptContextFactory.InitializeRuntime();
                Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
            });
        }

        [TestMethod]
        public void DestroyRuntime_NonInitializedRuntime_NothingChanges()
        {
            JavaScriptContextFactory.DestroyRuntime();
            Assert.IsFalse(JavaScriptContextFactory.IsInitialized);
        }

        [TestMethod]
        public void DestroyRuntime_NonInitializedRuntimeMultipleThreads_NothingChanges()
        {
            for (var i = 0; i < 1000; i++)
                new Thread(() =>
                {
                    JavaScriptContextFactory.DestroyRuntime();
                    Assert.IsFalse(JavaScriptContextFactory.IsInitialized);
                }).Start();
        }

        [TestMethod]
        public void DestroyRuntime_NonInitializedRuntimeThreadPool_NothingChanges()
        {
            Parallel.For(0, 1000, index =>
            {
                JavaScriptContextFactory.DestroyRuntime();
                Assert.IsFalse(JavaScriptContextFactory.IsInitialized);
            });
        }

        [TestMethod]
        public void DestroyRuntime_InitializedRuntime_InitializedNotSet()
        {
            JavaScriptContextFactory.InitializeRuntime();
            JavaScriptContextFactory.DestroyRuntime();
            Assert.IsFalse(JavaScriptContextFactory.IsInitialized);
        }

        [TestMethod]
        public void DestroyRuntime_InitializedRuntimeMultipleThreads_InitializedNotSet()
        {
            JavaScriptContextFactory.InitializeRuntime();
            for (var i = 0; i < 1000; i++)
                new Thread(() =>
                {
                    JavaScriptContextFactory.DestroyRuntime();
                    Assert.IsFalse(JavaScriptContextFactory.IsInitialized);
                }).Start();
        }

        [TestMethod]
        public void DestroyRuntime_InitializedRuntimeThreadPool_InitializedNotSet()
        {
            JavaScriptContextFactory.InitializeRuntime();
            Parallel.For(0, 1000, index =>
            {
                JavaScriptContextFactory.DestroyRuntime();
                Assert.IsFalse(JavaScriptContextFactory.IsInitialized);
            });
        }

        [ExpectedException(typeof (JavaScriptContextFactoryException))]
        [TestMethod]
        public void CreateContext_RuntimeNotInitialized_Throws()
        {
            Assert.IsFalse(JavaScriptContextFactory.IsInitialized);
            JavaScriptContextFactory.CreateContext();
        }

        [TestMethod]
        public void CreateContext_RuntimeInitialized_Works()
        {
            JavaScriptContextFactory.InitializeRuntime();
            Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
            JavaScriptContextFactory.CreateContext();
        }

        [TestMethod]
        public void CreateContext_MultipleThreads_Works()
        {
            JavaScriptContextFactory.InitializeRuntime();
            Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
            for (var i = 0; i < 1000; i++)
                new Thread(() => { JavaScriptContextFactory.CreateContext(); }).Start();
        }

        [TestMethod]
        public void CreateContext_ThreadPool_Works()
        {
            JavaScriptContextFactory.InitializeRuntime();
            Assert.IsTrue(JavaScriptContextFactory.IsInitialized);
            Parallel.For(0, 1000, index => { JavaScriptContextFactory.CreateContext(); });
        }
    }
}