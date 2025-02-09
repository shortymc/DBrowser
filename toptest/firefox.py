# -*- coding: utf-8 -*-

# Copyright 2012 splinter authors. All rights reserved.
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file.

from selenium.webdriver import DesiredCapabilities, Firefox
from selenium.webdriver.firefox.firefox_profile import FirefoxProfile
from splinter.driver.webdriver import (
    BaseWebDriver, WebDriverElement as WebDriverElement)
from splinter.driver.webdriver.cookie_manager import CookieManager
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.action_chains import ActionChains


class WebDriver(BaseWebDriver):

    driver_name = "Firefox"

    
    #def __init__(self, profile=None, extensions=None, user_agent=None,
    #             profile_preferences=None, fullscreen=False, wait_time=2,
    #             capabilities=None):
#//SECLAB Sun 30 Oct 2016 04:02:09 PM EDT START
    def __init__(self, profile=None, extensions=None, user_agent=None,
                 profile_preferences=None, fullscreen=False, wait_time=2,
                 capabilities=None, path=None):
#//SECLAB Sun 30 Oct 2016 04:02:14 PM EDT END

        firefox_profile = FirefoxProfile(profile)
        firefox_profile.set_preference('extensions.logging.enabled', False)
        firefox_profile.set_preference('network.dns.disableIPv6', False)

        firefox_capabilities = DesiredCapabilities().FIREFOX

        if capabilities:
            for key, value in capabilities.items():
                firefox_capabilities[key] = value

        if user_agent is not None:
            firefox_profile.set_preference(
                'general.useragent.override', user_agent)

        if profile_preferences:
            for key, value in profile_preferences.items():
                firefox_profile.set_preference(key, value)

        if extensions:
            for extension in extensions:
                firefox_profile.add_extension(extension)

        #SECLAB Sun 30 Oct 2016 04:00:56 PM EDT START
        self.driver = Firefox(firefox_profile, firefox_binary = path,
                              capabilities=firefox_capabilities)
        #self.driver = Firefox(firefox_profile,
        #                      capabilities=firefox_capabilities)

        #//SECLAB Sun 30 Oct 2016 04:01:11 PM EDT END
        if fullscreen:
            ActionChains(self.driver).send_keys(Keys.F11).perform()

        self.element_class = WebDriverElement

        self._cookie_manager = CookieManager(self.driver)

        super(WebDriver, self).__init__(wait_time)
