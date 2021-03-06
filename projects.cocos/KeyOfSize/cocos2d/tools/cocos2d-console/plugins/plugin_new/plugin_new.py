#!/usr/bin/python
# ----------------------------------------------------------------------------
# cocos2d "new" plugin
#
# Copyright 2013 (C) cocos2d-x.org
#
# License: MIT
# ----------------------------------------------------------------------------
'''
"new" plugin for cocos2d command line tool
'''

__docformat__ = 'restructuredtext'

# python
import os
import sys
import getopt
import ConfigParser

import cocos2d


def help():
    sys.exit(-1)


#
# Plugins should be a sublass of CCJSPlugin
#
class CCPluginNew(cocos2d.CCPlugin):

    @staticmethod
    def plugin_name():
      return "new"

    @staticmethod
    def brief_description():
        return "creates a new project"

    # parse arguments
    def parse_args(self, argv):
        """Custom and check param list.
        """
        from optparse import OptionParser
        # set the parser to parse input params
        # the correspond variable name of "-x, --xxx" is parser.xxx
        plugin_name = CCPluginNew.plugin_name()
        parser = OptionParser(
            usage=
            "\n\t%%prog %s, start GUI version."
            "\n\t%%prog %s -n <PROJECT_NAME> -k <PACKAGE_NAME> -l <cpp|lua|javascript> -p <PROJECT_PATH>"
            "\nSample:"
            "\n\t%%prog %s -n MyGame -k com.MyCompany.AwesomeGame -l javascript -p c:/mycompany" % (plugin_name, plugin_name, plugin_name)
        )
        parser.add_option("-n", "--name", metavar="PROJECT_NAME",help="Set a project name")
        parser.add_option("-k", "--package", metavar="PACKAGE_NAME",help="Set a package name for project")
        parser.add_option("-l", "--language",metavar="PROGRAMMING_NAME",
                            type="choice",
                            choices=["cpp", "lua", "javascript"],
                            help="Major programming language you want to use, should be [cpp | lua | javascript]")
        parser.add_option("-p", "--path", metavar="PROJECT_PATH",help="Set generate project path for project")

        # parse the params
        (opts, args) = parser.parse_args()
        if not opts.name:
            parser.error("-n or --name is not specified")

        if not opts.package:
            parser.error("-k or --package is not specified")

        if not opts.language:
            parser.error("-l or --language is not specified")

        if not opts.path:
            parser.error("-p or --path is not specified")

        return opts.name, opts.package, opts.language, opts.path


    # create from command
    def commandCreate(self, argv):
        name, package, language, path = self.parse_args(argv);
        from core import CocosProject
        project = CocosProject()
        project.createPlatformProjects(name, package, language, path)

    # main entry point
    def run(self, argv, dependencies):
        # use gui
        if len(sys.argv) == 2:
            try:
                from ui import createTkCocosDialog
                createTkCocosDialog()
            except ImportError:
                self.commandCreate(argv)
        else:
            self.commandCreate(argv)

