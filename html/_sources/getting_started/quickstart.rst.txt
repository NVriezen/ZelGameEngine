.. _getting_started_quickstart:

Quick Start
===========
This page describes the absolute minimum to get your project up and running


Setup
-----
To setup the engine, please refer to :ref:`Installation<getting_started_installation>`

Hello World
-----------
To check if our Visual Studio solution has been setup correctly we can try to print something.

Change ``zel_initialization`` to the code below.

.. code-block:: cpp

    void zel_initialization()
    {
        printf("Hello World!");
    }

When we now run the program, we should be able to see ``Hello World!`` appear in the command prompt.
If you don't see a command prompt when launching the program, make sure you selected the ``Debug`` configuration.

.. note:: Make sure you set **Zel_Windows** as the startup project in Visual Studio

Everything should now be setup and working properly.
Well done!


What's Next?
------------
Now that you have a working project you can check out the :ref:`Examples<getting_started_examples>`.

