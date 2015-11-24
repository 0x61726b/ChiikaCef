
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
 * @version @{chiika.ng.version}
 */
function handleSuccess(args)
{
    console.log("Success arguments");
    console.log(args);
}
function handleError(args)
{
    console.log("Error");
    console.log(args);
}
angular.module('homePage', [])
        .controller('HomePageCtrl', ['$scope',
            function ($scope) {
                $scope.card = {
                    name: 'Episodes Watched'
                };
                $scope.selectedIndex = 1;

                $scope.menuActions = [{
                        name: 'Verify User',
                        apiIndex: 0
                    },
                    {
                        name: 'Get Animelist From MAL',
                        apiIndex: 1
                    },
                    {
                        name: 'Get Animelist',
                        apiIndex: 1
                    }];
                $scope.onMenuClick = function (index)
                {
                    if (index === 0)
                    {
                        chiika.callApi(0, {user: "arkenthera", pass: "123asd456"}, handleSuccess, handleError);
                    }
                    if (index === 1)
                    {
                        chiika.callApi(1, "", handleSuccess, handleError);
                    }
                    if (index === 2)
                    {
                        chiika.callApi(2, "", handleSuccess, handleError);
                    }

                };
            }
        ])
        .directive('homePageDir', function () {
            return {
                restrict: 'E',
                templateUrl: 'homepage.html'
            };
        });

angular.module('animeList', [])
        .controller('AnimeListCtrl', ['$scope', '$q', '$timeout',
            function ($scope, $q, $timeout) {
                $scope.selected = [];

                $scope.query = {
                    order: 'title',
                    limit: 5,
                    page: 1
                };
                $scope.test1 = 5;
                $scope.userAnimeList = {};
                $scope.updateAngularElement = function (args, list)
                {
                    if (list === 1)
                    {
                        $scope.watchingList.count = args.length;
                        $scope.watchingList.data = args;
                    }
                    if(list === 2)
                    {
                        $scope.completedList.count = args.length;
                        $scope.completedList.data = args;
                    }

                };
                //Default values
                $scope.watchingList = {
                    "count": 4,
                    "data": [{
                            "title": 'Owarimonogatari',
                            "progress": {
                                "value": 0.4
                            },
                            "progressString": "7/25",
                            "type": 'Tv',
                            "score": {
                                "value": 8
                            },
                            "season": 'Fall 2015'
                        }, {
                            "title": 'Rakudai Kishi no Cavalary',
                            "progress": {
                                "value": 0.2
                            },
                            "progressString": "2/25",
                            "type": 'Tv',
                            "score": '-',
                            "season": 'Fall 2015'
                        }, {
                            "title": 'Noragami Aragoto',
                            "progress": {
                                "value": 0.75
                            },
                            "progressString": "20/25",
                            "type": 'Tv',
                            "score": '-',
                            "season": 'Fall 2015'
                        }, {
                            "title": 'Gakusen Asterisk',
                            "progress": {
                                "value": 0.9
                            },
                            "progressString": "24/25",
                            "type": 'Tv',
                            "score": '-',
                            "season": 'Fall 2015'
                        }]
                };
                $scope.completedList = {
                    "count": 4,
                    "data": [{
                            "title": 'Owarimonogatari',
                            "progress": {
                                "value": 0.4
                            },
                            "progressString": "7/25",
                            "type": 'Tv',
                            "score": {
                                "value": 8
                            },
                            "season": 'Fall 2015'
                        }, {
                            "title": 'Rakudai Kishi no Cavalary',
                            "progress": {
                                "value": 0.2
                            },
                            "progressString": "2/25",
                            "type": 'Tv',
                            "score": '-',
                            "season": 'Fall 2015'
                        }, {
                            "title": 'Noragami Aragoto',
                            "progress": {
                                "value": 0.75
                            },
                            "progressString": "20/25",
                            "type": 'Tv',
                            "score": '-',
                            "season": 'Fall 2015'
                        }, {
                            "title": 'Gakusen Asterisk',
                            "progress": {
                                "value": 0.9
                            },
                            "progressString": "24/25",
                            "type": 'Tv',
                            "score": '-',
                            "season": 'Fall 2015'
                        }
]
                };
                $scope.droppedList = {
                    "count": 4,
                    "data": [{
                            "title": 'Owarimonogatari',
                            "progress": {
                                "value": 0.4
                            },
                            "progressString": "7/25",
                            "type": 'Tv',
                            "score": {
                                "value": 8
                            },
                            "season": 'Fall 2015'
                        }, {
                            "title": 'Rakudai Kishi no Cavalary',
                            "progress": {
                                "value": 0.2
                            },
                            "progressString": "2/25",
                            "type": 'Tv',
                            "score": '-',
                            "season": 'Fall 2015'
                        }, {
                            "title": 'Noragami Aragoto',
                            "progress": {
                                "value": 0.75
                            },
                            "progressString": "20/25",
                            "type": 'Tv',
                            "score": '-',
                            "season": 'Fall 2015'
                        }, {
                            "title": 'Gakusen Asterisk',
                            "progress": {
                                "value": 0.9
                            },
                            "progressString": "24/25",
                            "type": 'Tv',
                            "score": '-',
                            "season": 'Fall 2015'
                        }]
                };
                $scope.onHoldList = {
                    "count": 4,
                    "data": [{
                            "title": 'Owarimonogatari',
                            "progress": {
                                "value": 0.4
                            },
                            "progressString": "7/25",
                            "type": 'Tv',
                            "score": {
                                "value": 8
                            },
                            "season": 'Fall 2015'
                        }, {
                            "title": 'Rakudai Kishi no Cavalary',
                            "progress": {
                                "value": 0.2
                            },
                            "progressString": "2/25",
                            "type": 'Tv',
                            "score": '-',
                            "season": 'Fall 2015'
                        }, {
                            "title": 'Noragami Aragoto',
                            "progress": {
                                "value": 0.75
                            },
                            "progressString": "20/25",
                            "type": 'Tv',
                            "score": '-',
                            "season": 'Fall 2015'
                        }, {
                            "title": 'Gakusen Asterisk',
                            "progress": {
                                "value": 0.9
                            },
                            "progressString": "24/25",
                            "type": 'Tv',
                            "score": '-',
                            "season": 'Fall 2015'
                        }]
                };
                $scope.ptwList = {
                    "count": 4,
                    "data": [{
                            "title": 'Owarimonogatari',
                            "progress": {
                                "value": 0.4
                            },
                            "progressString": "7/25",
                            "type": 'Tv',
                            "score": {
                                "value": 8
                            },
                            "season": 'Fall 2015'
                        }, {
                            "title": 'Rakudai Kishi no Cavalary',
                            "progress": {
                                "value": 0.2
                            },
                            "progressString": "2/25",
                            "type": 'Tv',
                            "score": '-',
                            "season": 'Fall 2015'
                        }, {
                            "title": 'Noragami Aragoto',
                            "progress": {
                                "value": 0.75
                            },
                            "progressString": "20/25",
                            "type": 'Tv',
                            "score": '-',
                            "season": 'Fall 2015'
                        }, {
                            "title": 'Gakusen Asterisk',
                            "progress": {
                                "value": 0.9
                            },
                            "progressString": "24/25",
                            "type": 'Tv',
                            "score": '-',
                            "season": 'Fall 2015'
                        }]
                };

                $scope.getTypes = function () {
                    return ['Tv'];
                };
                $scope.onorderchange = function (order) {
                    var deferred = $q.defer();

                    $timeout(function () {
                        deferred.resolve();
                    }, 2000);

                    return deferred.promise;
                };
                $scope.onpagechange = function (page, limit) {
                    var deferred = $q.defer();

                    $timeout(function () {
                        deferred.resolve();
                    }, 2000);

                    return deferred.promise;
                };

            }
        ])
        .directive('animeListDir', function () {
            return {
                scope: {},
                restrict: 'E',
                templateUrl: 'animeList.html',
                controller: 'AnimeListCtrl',
                controllerAs: 'ctrl',
                replace: false
            };
        });

angular.module('animeTable', [])
        .controller('AnimeTableCtrl', ['$scope',
            function ($scope) {
                this.animeList = $scope.animeList;
            }
        ])
        .directive('animeTableDir', function () {
            return {
                scope: {
                    animeList: '=animeList'
                },
                restrict: 'E',
                templateUrl: 'animeListTable.html',
                replace: false,
                controller: 'AnimeTableCtrl',
                controllerAs: 'ctrl'
            };
        });

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
 * @version @{chiika.ng.version}
 */
angular.module('mangaList', [])
        .controller('MangaListCtrl', ['$scope',
            function ($scope) {
                $scope.card = {
                    name: 'MangaList'
                };
                //Default values
                this.readingList = [{
                        title: 'Sakurasou no Pet na Kanojo',
                        progress: '7/25',
                        type: 'Tv',
                        score: '10',
                        season: 'Fall 2015'
                    }, {
                        title: 'Shigatsu wa Kimi no Uso',
                        progress: '7/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    }, {
                        title: 'Horimiya',
                        progress: '7/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    }, {
                        title: 'Chikan Otoko',
                        progress: '7/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    }];
                this.completedList = [{
                        title: 'Watashitachi no Shiawase na Jikan',
                        progress: '25/25',
                        type: 'Tv',
                        score: '10',
                        season: 'Fall 2015'
                    }, {
                        title: 'Nisekoi',
                        progress: '12/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    }, {
                        title: 'Last Game',
                        progress: '12/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    }, {
                        title: 'Akagami no Shirayuki-hime',
                        progress: '12/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    }, {
                        title: 'Tsurezure Children',
                        progress: '12/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    }, {
                        title: 'To LOVE-Ru',
                        progress: '3/3',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    } ];
                this.droppedList = [{
                        title: 'Clannad',
                        progress: '7/25',
                        type: 'Tv',
                        score: '10',
                        season: 'Fall 2015'
                    }, {
                        title: 'Toradora',
                        progress: '7/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    }, {
                        title: 'Tonari no Kaibutsu-kun',
                        progress: '7/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    }, {
                        title: 'Kiss x Sis',
                        progress: '7/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    }];
                this.onholdList = [{
                        title: 'Sakamichi no Apollon',
                        progress: '7/25',
                        type: 'Tv',
                        score: '10',
                        season: 'Fall 2015'
                    }, {
                        title: 'Shishunki Bitter Change',
                        progress: '7/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    }, {
                        title: 'Asobi ni Iku yo!',
                        progress: '7/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    }, {
                        title: 'Toaru Kagaku no Railgun',
                        progress: '7/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    },
                    {
                        title: 'Yamada-kun to 7-nin no Majo',
                        progress: '7/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    },
                    {
                        title: 'Durarara!!',
                        progress: '7/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    }];
                this.plantoreadList = [{
                        title: 'So Ra No Wo To',
                        progress: '7/25',
                        type: 'Tv',
                        score: '10',
                        season: 'Fall 2015'
                    }, {
                        title: 'Kanokon',
                        progress: '7/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    }, {
                        title: 'Octave',
                        progress: '7/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    }, {
                        title: 'Come Come Vanilla!',
                        progress: '7/12',
                        type: 'Tv',
                        score: '-',
                        season: 'Fall 2015'
                    }];
            }
        ])
        .directive('mangaListDir', function () {
            return {
                scope: {},
                restrict: 'E',
                templateUrl: 'mangaList.html',
                controller: 'MangaListCtrl',
                controllerAs: 'ctrl',
                replace: true
            };
        });

angular.module('mangaTable', [])
        .controller('MangaTableCtrl', ['$scope',
            function ($scope) {
                this.mangaList = $scope.mangaList;
            }
        ])
        .directive('mangaTableDir', function () {
            return {
                scope: {
                    mangaList: '=mangaList'
                },
                restrict: 'E',
                templateUrl: 'mangaListTable.html',
                replace: true,
                controller: 'MangaTableCtrl',
                controllerAs: 'ctrl'
            };
        });

angular
  .module('menuDemoPosition', ['ngMaterial'])
  .config(function($mdIconProvider) {
    $mdIconProvider
      .iconSet("hamburger", 'assets/svg/hamburger.svg', 24)
      .iconSet("social", 'img/icons/sets/social-icons.svg', 24)
      .defaultIconSet('/assets/svg/hamburger.svg', 24);
  })
  .controller('PositionDemoCtrl', function DemoCtrl($mdDialog) {
    var originatorEv;
    this.openMenu = function($mdOpenMenu, ev) {
      originatorEv = ev;
      $mdOpenMenu(ev);
    };
    this.announceClick = function(index) {
      $mdDialog.show(
        $mdDialog.alert()
          .title('You clicked!')
          .content('You clicked the menu item at index ' + index)
          .ok('Nice')
          .targetEvent(originatorEv)
      );
      originatorEv = null;
    };
  });

/**
 *
 *Finally register modules
 *
 *
 * @name settings
 * @namespace
 *
 * @memberOf chiika
 *
 * @version @{chiika.ng.version}
 */
       angular
           .module('chiika', ['ngMaterial', 'md.data.table','homePage','animeList','animeTable','menuDemoPosition'])
           .config(function($mdThemingProvider) {

               $mdThemingProvider.theme('default')
                   .primaryPalette('teal')
                   .accentPalette('indigo');

           })
           .controller('AppCtrl', function($scope, $mdSidenav) {
               $scope.openLeftMenu = function() {
                   $mdSidenav('left').toggle();
               };
           });