# Importing the module
from twython import Twython

#Setting these as variables will make them easier for future edits
app_key = "YOUR_APP_KEY"
app_secret = "YOUR_APP_SECRET"
oauth_token = "YOUR_OAUTH_TOKEN"
oauth_token_secret = "YOUR_OAUTH_TOKEN_SECRET"

#Prepare your twitter, you will need it for everything
twitter = Twython(app_key, app_secret, oauth_token, oauth_token_secret)
#The above should just be a single line, without the break

#The obligatory first status update to test
twitter.update_status(status="Hello world.")
