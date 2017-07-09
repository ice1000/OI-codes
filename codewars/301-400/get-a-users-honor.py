import urllib.request
import re

def get_honor(username):
    a = urllib.request.urlopen("https://www.codewars.com/api/v1/users/" + username).read().decode("utf-8")
    return int(re.search("honor\":(.*?),", a).group(1))
#
