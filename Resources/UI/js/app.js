angular.module('homePage',[])
.controller('EpisodesWatchedCtrl', ['$scope', function($scope) {
  $scope.card = {
    name: 'Episodes Watched'
  };
}])
.directive('epWatched', function() {
  return {
    restrict: 'E',
    templateUrl: 'cards_episodes_watched.html'
  };
});

angular.module('chiikaAngular', ['homePage']);