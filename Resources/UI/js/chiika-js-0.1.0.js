
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
    self.updateAngularElement = function(element,args,index)
    {
        angular.element(element).scope().updateAngularElement(args,index);
        angular.element(element).scope().$apply();
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
var AnimeModel = function ()
{
    var self = this,
            id = 0,
            title = "",
            english = "",
            episodeCount = "",
            type = "",
            status = "",
            startDate = "",
            endDate = "",
            synopsis = "",
            season = "",
            tags,
            premiered = "",
            producers = "",
            duration = 0,
            score = 0,
            ranked = 0,
            popularity = 0;
    self.getSeason = function()
    {
        var parts = this.startDate.split("-");
        var year = parts[0];
        var month = parts[1];

        var iMonth = parseInt(month);

        if(iMonth > 0 && iMonth <4)
        {
            return "Winter " +year;
        }
        if(iMonth > 3 && iMonth < 7)
        {
            return "Spring " + year;
        }
        if(iMonth > 6 && iMonth < 10)
        {
            return "Summer " + year;
        }
        if(iMonth > 9 && iMonth <= 12)
        {
            return "Fall " + year;
        }
        return "Unkown Season";
    };
    self.getStatus = function()
    {
        if(this.status === "1")
        {
            return "Watching";
        }
        if(this.status === "2")
        {
            return "Completed";
        }
        if(this.status === "3")
        {
            return "On Hold";
        }
        if(this.status === "4")
        {
            return "Dropped";
        }
        if(this.status === "6")
        {
            return "Plan to Watch";
        }
    };
    self.getType = function()
    {
        if(this.type === "1")
        {
            return "Tv";
        }
        if(this.type === "2")
        {
            return "Ova";
        }
        if(this.type === "3")
        {
            return "Movie";
        }
    };
};
var UserAnimeModel = function ()
{
    var self = this, anime = null,
            progress = {value: 0},
            progressString = "",
            score = {value: 0},
            scoreString = "";

    self.getProgressString = function ()
    {
        if(this.anime.episodeCount === "0")
        {
            return "-";
        }
        else
        {
           return this.progress.value + "/" + this.anime.episodeCount;
        }
    };
    self.getScoreString = function ()
    {
        if (this.score === 0)
        {
            return "-";
        }
        else
        {
            return this.score;
        }
    };
};
var AngularViewModel = function()
{
    var self = this,
            title = "",
            progress = { value: 0 },
            progressString = "",
            type = "",
            score = { value:0 },
            scoreString = "",
            season = "";
    self.setModel = function(model)
    {
        this.title = model.anime.title;
        this.progress = model.progress;
        this.progressString = model.getProgressString();
        this.type = model.anime.getType();
        this.score = model.score;
        this.scoreString = model.getScoreString();
        this.season = model.anime.getSeason();
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
var UserAnimeList = function ()
{
    var self = this,
            animeList;

    self.getUserAnimeList = function ()
    {
        return animeList;
    };
    self.setUserAnimeList = function (a)
    {
        animeList = a;
        console.log("Setting user anime list..size: " + animeList.length);
        console.log(animeList[0]);
        var angularWatchingModelList = [];
        var angularCompletedModelList = [];
        var index = 0;
        for (index; index < animeList.length; index++)
        {
            var listIdentifier = animeList[index].my_status;


            var animeModel = new AnimeModel();
            animeModel.title = animeList[index].anime.series_title;
            animeModel.type = animeList[index].anime.series_type;
            animeModel.status = animeList[index].series_status;
            animeModel.startDate = animeList[index].anime.series_start;
            animeModel.endDate = animeList[index].anime.series_end;
            animeModel.episodeCount = animeList[index].anime.series_episodes;
            var userAnimeModel = new UserAnimeModel();
            userAnimeModel.anime = animeModel;
            userAnimeModel.progress = {value: animeList[index].my_watched_episodes};
            userAnimeModel.score = {value: animeList[index].my_score};

            var angularModel = new AngularViewModel();
            angularModel.setModel(userAnimeModel);

            if( listIdentifier === "1")
            {
               angularWatchingModelList.push(angularModel);
            }
            if( listIdentifier === "2")
            {
               angularCompletedModelList.push(angularModel);
            }
        }
        console.log(angularWatchingModelList);


        apiFunctions.updateAngularElement($("#watchingWrapper"), angularWatchingModelList,1);

        apiFunctions.updateAngularElement($("#completedWrapper"), angularCompletedModelList,2);

    };
}, _userAnimeList;
_userAnimeList = new UserAnimeList();

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
        apiFunctions.callApi(1, this.handleAnimelistCallback, this.handleAnimelistError, "", true);
    };
    self.callApi = function (apiIndex, args, success, error)
    {
        apiFunctions.callApi(apiIndex, success, error, args, false);
    };
    self.handleAnimelistCallback = function(args)
    {
        _userAnimeList.setUserAnimeList(args[0]);
    };
    self.handleAnimelistError = function(args)
    {
        console.log(args);
    };
}, chiika;
chiika = new Chiika();
$(document).ready(function()
{
    chiika.getAnimeList();
});
