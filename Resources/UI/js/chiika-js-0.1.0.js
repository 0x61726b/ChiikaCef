
/**
*
*
*
*
* @name API function list
* @namespace
*
*
* @version 0.1.0
* @since 0.0.0
*/
var ApiList = [
    {
        name:"ChiikaVerifyUser",
        index:0,
        argCount:1
    },
    {
        name:"ChiikaGetAnimelistRequest",
        index:1,
        argCount:0
    },
    {
        name:"ChiikaGetAnimelist",
        index:2,
        argCount:0
    }
];

/**
 *
 *
 *
 *
 * @name Utility classes
 * @namespace
 *
 *
 * @version 0.1.0
 * @since 0.0.0
 */

var ApiFuncCaller = function ()
{
    var self = this;


    self.callApi = function (apiIndex, success, error, args, delayed)
    {
        var index;
        if (typeof ApiList[apiIndex] === "undefined")
        {
            console.log("Trying to call a API function that doesnt exist.");
            return;
        }
        console.log("Trying to execute" + ApiList[apiIndex].name + "... with arguments: ");
        console.log(args);

        if (typeof window[ApiList[apiIndex].name] === "function")
        {
            console.log("Executing call..." + apiIndex);
            window[ApiList[apiIndex].name](success, error, args);
        } else
        {
            console.log("You can't call this function outside of Chiika.");
        }
    };
}, apiFunctions;


apiFunctions = new ApiFuncCaller();

/**
*
*
*
*
* @name Anime Model
* @namespace
*
*
* @version 0.1.0
*/
var AnimeModel = function()
{
    var self = this,
            id = 0,
            title = "",
            english = "",
            episodeCount = "",
            type = "",
            status = "",
            startDate = "",
            endDate = "" ,
            synopsis = "",
            tags,
            premiered = "",
            producers = "",
            duration = 0,
            score = 0,
            ranked = 0,
            popularity = 0;
    self.getId = function()
    {
        return id;
    };
    self.getTitle = function()
    {
        return title;
    };
    self.getEnglish = function()
    {
        return english;
    };
    self.getEpisodeCount = function()
    {
        return episodeCount;
    };
    self.getType = function()
    {
        return type;
    };
    self.getStatus = function()
    {
        return status;
    };
    self.getStartDate = function()
    {
        return startDate;
    };
    self.getEndDate = function()
    {
        return endDate;
    };
    self.getSynopsis = function()
    {
        return synopsis;
    };
    self.getTags = function()
    {
        return tags;
    };
    self.getPremiered = function()
    {
        return premiered;
    };
    self.getProducers = function()
    {
        return producers;
    };
    self.getDuration = function()
    {
        return duration;
    };
    self.getScore = function()
    {
        return score;
    };
    self.getRanked = function()
    {
        return ranked;
    };
    self.getPopularity = function()
    {
        return popularity;
    };
};

/**
*
*
*
*
* @name Anime List
* @namespace
*
*
* @version 0.1.0
*/
var UserAnimeList = function()
{
    var self = this,
            userAnimeList;

    self.getUserAnimeList = function()
    {
        return userAnimeList;
    };
    self.setUserAnimeList = function(animeList)
    {
        userAnimeList = animeList;
    };
};

/**
*
*
*
*
* @name User Model
* @namespace
*
*
* @version 0.1.0
*/
var User = function()
{
    var self = this,
            userName = "",
            animeInfo =
            {
                watching:0,
                completed:0,
                onHold:0,
                dropped:0,
                planToWatch:0,
                daysSpent:0
            },
            mangaInfo =
            {
                reading:0,
                read:0,
                onHold:0,
                dropped:0,
                planToRead:0,
                daysSpent:0
            };


    self.getUserAnimeInfo = function()
    {
        return animeInfo;
    };
    self.getUserMangaInfo = function()
    {
        return mangaInfo;
    };
};

/**
*
*
*
*
* @name settings
* @namespace
*
* @memberOf chiika
*
* @version 0.1.0
* @since 0.0.0
*/
var Settings = function()
{
    var self = this,
            libraryPath = "",
            syncInterval = 150,
            windowSettings =
            {
              startMinimized:false,
              startWithWin:false,
              rememberPos:false,
              rememberSize:false
            },
            globalColor;

    self.getLibraryPath = function()
    {
        return libraryPath;
    };

    self.getSyncInterval = function()
    {
        return syncInterval;
    };

    self.getWindowSettings = function()
    {
        return windowSettings;
    };

    self.getGlobalColor = function()
    {
        return globalColor;
    };
};

/**
 *
 *
 *
 *
 * @name Chiika JS
 * @namespace
 *
 *
 * @version 0.1.0
 * @since 0.0.0
 */
var Chiika = function ()
{
    var self = this, isInitialized = false, settings;

    self.getInitialized = function ()
    {
        return isInitialized;
    };
    self.getSettings = function ()
    {
        return settings;
    };
    self.getUserSettings = function (callback)
    {
        self.callApi("getUserSettings", callback);
    };
    self.setUserSettings = function (args, callback)
    {
        self.callApi("setUserSettings", args, callback);
    };
    self.getAnimeList = function (success, error)
    {
        apiFunctions.callApi(1, success, error, "", true);
    };
    self.callApi = function (apiIndex, args, success, error)
    {
        apiFunctions.callApi(apiIndex, success, error, args, false);
    };
}, chiika;
function handleAnimelistCallback(args)
{
    console.log(args);
}
function handleAnimelistError(args)
{
    console.log(args);
}

chiika = new Chiika();
//window.ChiikaGetAnimelist(handleAnimelistCallback, handleAnimelistError, "");
