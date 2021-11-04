<?php

    require_once "databasehandler.inc.php";
    require_once "functionlibrary.inc.php";

    if(checkTrigger($conn)) {
       
        // on récupère dans un boucle les informations de chaques machines 
        for ($i = 1; $i < 4; $i++) {
            getEngineInfos($conn, $i);
        }


        // on repasse la detente à FALSE pour signifier que le changement a été prit en compte et que on attend le prochain
        //activateTrigger($conn);

        header("location: ../../server?reload=true");
        exit();
    }

    header("location: ../../server?reload=false");
    exit();