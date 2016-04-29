using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace V8.Net.Tests
{
    [TestClass]
    public class JavaScriptContextFactoryTest
    {
        [TestMethod]
        public void InitializeRuntime_NonInitializedRuntime_InitializedSet()
        {

        }

        [TestMethod]
        public void InitializeRuntime_NonInitializedRuntimeMultipleThreads_InitializedSet()
        {

        }

        [TestMethod]
        public void InitializeRuntime_InitializedRuntime_NothingChanges()
        {

        }

        [TestMethod]
        public void InitializeRuntime_InitializedRuntimeMultipleThreads_NothingChanges()
        {

        }

        [TestMethod]
        public void DestroyRuntime_NonInitializedRuntime_NothingChanges()
        {

        }

        [TestMethod]
        public void DestroyRuntime_NonInitializedRuntimeMultipleThreads_NothingChanges()
        {

        }

        [TestMethod]
        public void DestroyRuntime_InitializedRuntime_InitializedNotSet()
        {

        }

        [TestMethod]
        public void DestroyRuntime_InitializedRuntimeMultipleThreads_InitializedNotSet()
        {

        }
    }
}
