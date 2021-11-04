<!-- 
	03/11/2021
	server/server.php
	CODE DE LA PAGE D'INTERFACE POUR AVOIR LES
    INFORMATIONS SUR LES MACHINES EN DIRECT
-->

<?php 
    require("php/head.php");

    $firstPourcentage = 80;
    $secondPourcentage = 20;
    $thirdPourcentage = 10;
    $machineIsOn = false;
?>

<main>
    <aside>
        <section>
            <h1> &#128223 Machine 1 </h1>
            <br>
            &#128205 Local 2 coté droit de la porte <br>
            temps d'allumage :  <br>
            date du dernier arret <br>
            allumé ou pas
        </section>
        <section>
             <h1> &#128250 Machine 2  </h1>
        </section>
        <!-- <svg class="machine-on-off" viewBox="0 0 14.2 20.6">
            <g transform="translate(-37.1 -88.9)">
                <path d="m46.7 
                    88.9c-0.285-0.0043-0.468 0.213-0.468 0.213l-8.99 11.7s-0.308 
                    0.34-0.141 0.716c0.167 0.376 0.547 0.363 0.547 0.363l5.52-4e-3 
                    -2.17 6.71s-0.206 0.485 0.251 0.754c0.457 0.269 0.783-0.119 
                    0.783-0.119l8.99-11.7s0.307-0.34 0.14-0.716c-0.167-0.376-0.547-0.363-0.547-0.363l-5.52 
                    0.0041 2.17-6.71s0.206-0.485-0.251-0.754c-0.114-0.0672-0.22-0.0931-0.315-0.0946z"
                fill="<?= ($machineIsOn ? "var(--yellow)" : "var(--dark)")?>"/>
            </g>
        </svg> -->

</aside>
    <section>
        <h1> &#128202 Infos Machines </h1>

        <div class="flex-wrapper">
            <div class="single-chart">
                <svg viewBox="0 0 36 36" class="circular-chart orange">
                    <path class="circle-bg"
                        d="M18 2.0845
                            a 15.9155 15.9155 0 0 1 0 31.831
                            a 15.9155 15.9155 0 0 1 0 -31.831"
                    />
                    <path class="circle"
                        stroke-dasharray="<?=$firstPourcentage?>, 100"
                        d="M18 2.0845
                            a 15.9155 15.9155 0 0 1 0 31.831
                            a 15.9155 15.9155 0 0 1 0 -31.831"
                    />
                    <text x="18" y="20.35" class="percentage">
                        <?=$firstPourcentage?>%
                    </text>
                </svg>
            </div>

            <div class="single-chart">
                <svg viewBox="0 0 36 36" class="circular-chart green">
                    <path class="circle-bg"
                    d="M18 2.0845
                        a 15.9155 15.9155 0 0 1 0 31.831
                        a 15.9155 15.9155 0 0 1 0 -31.831"
                    />
                    <path class="circle"
                    stroke-dasharray="<?=$secondPourcentage?>, 100"
                    d="M18 2.0845
                        a 15.9155 15.9155 0 0 1 0 31.831
                        a 15.9155 15.9155 0 0 1 0 -31.831"
                    />
                    <text x="18" y="20.35" class="percentage">
                        <?=$secondPourcentage?>%
                    </text>
                </svg>
            </div>

            <div class="single-chart">
                <svg viewBox="0 0 36 36" class="circular-chart blue">
                    <path class="circle-bg"
                        d="M18 2.0845
                            a 15.9155 15.9155 0 0 1 0 31.831
                            a 15.9155 15.9155 0 0 1 0 -31.831"
                    />
                    <path class="circle"
                        stroke-dasharray="<?=$thirdPourcentage?>, 100"
                        d="M18 2.0845
                            a 15.9155 15.9155 0 0 1 0 31.831
                            a 15.9155 15.9155 0 0 1 0 -31.831"
                    />
                    <text x="18" y="20.35" class="percentage">
                        <?=$thirdPourcentage?>%
                    </text>
                </svg>
            </div>
        </div>
    </section>
    <section>
         <h1> &#128225 Machine 3  </h1>
    </section>
    <section>
         <h1> &#128291 Trucs en plus  </h1>
    </section>
</main>

<?php 
    require("php/foot.php");
?>