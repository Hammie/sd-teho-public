// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Что вы хотели? Спрашивайте.", "Я слушаю вас, что за вопрос?"), "Второй раз за день вы пытаетесь задать ворпос...", "В третий раз за день вы опять пытаетесь задать вопрос...",
                          "Да когда же это кончится?! У меня дел полно по управлению делами города, а ты все вопросы пытаешься задать!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Не сейчас, не место и не время..."), "Да, верно... Но не сейчас, позже...",
                      "Задам, задам... Только позже...", "Извините, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToGovernor")
			{
				link.l1 = "Ваша cветлость, у меня великолепные новости, совершенно не терпящие отлагательств! Мне удалось захватить самого Бартоломео Португальца, и мерзавец, под охраной, ждет справедливого суда! А я – скромной благодарности от Компании...";
				link.l1.go = "Portugal";
			}
			//Португалец
			
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "governor")
			{
				link.l1 = "Я прибыл по вашему настоятельному приглашению, минхер губернатор...";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_battle_complete")
			{
				link.l1 = "Я прибыл по вопросу об английских шпионах, минхер губернатор...";
				link.l1.go = "FMQN_7";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Вы уже все забрали. Что вам еще нужно?", "Неужели осталось еще что-то, что вы не прихватили?");
            link.l1 = RandPhraseSimple("Осматриваюсь напоследок...", "Проверяю, может забыл"+ GetSexPhrase("","а") +" что забрать...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Jason, Португалец
		case "Portugal":
			dialog.text = "Бартоломео... Барт Португалец в моем городе?! Живой?!!";
			link.l1 = "Да, ваша светлость, и он, повторяю, под надежной охраной. Я передам его в руки правосудия, сразу, как получу обещанный Компанией за его персону вексель. Впрочем, меня устроят и золотые дублоны...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Какие векселя, какие дублоны, да вы с ума сошли! О чем вы думали, когда тащили этого зверя в мой город?! Если он здесь, значит, и его фрегат где-то поблизости, а его люди могут быть в самом городе, прямо в настоящее время!!";
			link.l1 = "Тех, что были с ним, мне пришлось прикончить, не знаю, есть ли другие, но, вряд ли это так важно, ведь Бартоломью...";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Важно! Да вы хоть понимаете что натворили?! 'Альбатрос' рядом с островом, а вам заблагорассудилось повязать пирата, чья жестокость пугает даже его кровожадных соотечественников? Притом, что несколько сотен его головорезов ошиваются где-то неподалеку! Убирайтесь! Убирайтесь с острова немедленно! И забирайте с собой этого разбойника!";
			link.l1 = "Но послушайте, а как же обещанная награда и...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Я не хочу, чтобы из-за вашей алчности и мстительности Компании, мой город сожгли у меня на глазах! В моем форту одни новобранцы, и половина из них разбежится, когда узнает, кто и зачем идет на их равелины! А потом будет резня... я не собираюсь так рисковать, вы слышали?! Убирайтесь, и, если Компании так нужна его голова – везите его сами на Кюрасао!\nНемедленно, пока еще не поздно! И делайте с ним что хотите – хоть за борт выбрасывайте, но только не в моем городе!\nГанс! Ганс, где ты, ленивый олух! Подай немедля настой валерианы, и кто-нибудь, Бога ради, вышвырните этого авантюриста из моей резиденции!";
			link.l1 = "Но, ваша светлость...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Marigo_town", "reload", "reload3_back", "PortugalOutResidence");
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			dialog.text = "Очень хорошо! Скажите, капитан, на подходе к Синт-Маартену вы не встречали английского военного судна? Или торгового?";
			link.l1 = "Нет, минхер. Ни военные, ни торговые суда под флагом Англии мне в ваших водах не встречались.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Ясно. Вы надолго к нам?";
			link.l1 = "Думаю задежаться в вашей колонии дня три...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "В таком случае у меня к вам предложение. По данным нашей разведки, на остров могут прибыть английские шпионы. За достоверную информацию о любом подозрительном корабле, особенно английском, либо о не внушающих доверия личностях, расхаживающих по бухтам и джунглям, я объявил награду в десять тысяч песо. В случае же поимки шпионов, либо содействии в их задержании, вознаграждение будет значительно увеличено\nЯ довожу это до сведения всех без исключения гражданских капитанов, прибывающих в наш порт. Так что если мое предложение вас заинтересовало - можете между делом прорейдировать акваторию Синт-Маартена и прочесать бухты, удобные для высадки\nВ водах нашей колонии вы можете повстречать корвет 'Зеепард' - не беспокойтесь, он патрулирует акваторию Синт-Маартена, и в случае обнаружения англичан, вы всегда можете обратиться к капитану корвета за помощью.";
			link.l1 = "Сожалею, ваша Светлость, но я прибыл исключительно по торговым делам, и после их завершения и пополнения припасов, буду вынужден как можно скорее продолжить свой путь.";
			link.l1.go = "FMQN_3";
			link.l2 = "Заманчивое предложение! Я, пожалуй, воспользуюсь им, и хорошенько порыскаю по водам и берегам вашего острова. Может, даже задержусь...";
			link.l2.go = "FMQN_5";
		break;
		
		case "FMQN_3":
			dialog.text = "Это была просто информация к сведению, капитан. Вас никто ни к чему не обязывает. Если вдруг увидите что-то подозрительное - вы знаете, куда идти.";
			link.l1 = "Да, минхер, я понял. До свидания!";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			DialogExit();
			pchar.questTemp.FMQN = "way_eng_1";
			AddQuestRecord("FMQ_Nevis", "8");
			chrDisableReloadToLocation = false;
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_5":
			dialog.text = "Прекрасно, капитан! Раз вы так серьезно решили взяться за дело - зайдите еще и к нашему коменданту. Он отвечает за розыск шпионов и может дать вам дополнительную полезную информацию.";
			link.l1 = "Хорошо, минхер. Отправляюсь в комендатуру.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			DialogExit();
			pchar.questTemp.FMQN = "way_div";
			AddQuestRecord("FMQ_Nevis", "9");
			chrDisableReloadToLocation = false;
		break;
		
		case "FMQN_7":
			dialog.text = "Мы ждали вас, минхер "+GetFullName(pchar)+". Выражаю вам личную благодарность и благодарность жителей колонии за проявленную вами инициативу в ликвидации опасной шайки английских диверсантов. Вам полагается обещанное вознаграждение в 10 000 песо, а также большая премия - лицензия Голландской Вест-Индской торговой Компании сроком на полгода. Это очень ценный документ, надеюсь, вы в курсе?";
			link.l1 = "Конечно! Лицензия на полгода - это действительно дорого стоит.";
			link.l1.go = "FMQN_8";
		break;
		
		case "FMQN_8":
			dialog.text = "Пожалуйста, получите вашу награду. И кроме признательности материальной, вам обеспечен почет и уважение среди голландских поселенцев и благосклонность властей. Весь город только о вас и говорит. Будем рады видеть вас в Филипсбурге и впредь.";
			link.l1 = "Это стоит не меньше, минхер. Благодарю вас, был рад оказать вам помощь. А теперь мне пора откланяться.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandBattleComplete");
		break;
		
		// Jason НСО
		case "tomas":
			dialog.text = "Мы капитулируем! Во имя всего святого, прошу вас, не устраивайте грабеж и мародерство в Филипсбурге! Я готов выслушать ваши требования!";
			link.l1 = "Не беспокойтесь за жителей, минхер. Подданным французской короны незачем бояться французских солдат.";
			link.l1.go = "tomas_1";
		break;
		
		case "tomas_1":
			dialog.text = "Французской короны?..";
			link.l1 = "Именно. Этот остров принадлежит Франции, а вы здесь - всего лишь арендаторы. Наглые арендаторы, вообразившие себе, что можете присвоить остров в собственность. С сегодняшнего дня любой голландской власти на Синт-Маартене пришел конец. Это ясно?";
			link.l1.go = "tomas_2";
		break;
		
		case "tomas_2":
			dialog.text = "Но... Но что будет с нами, с голландскими солдатами, сдавшимися вам, и с ранеными в бою? И что...";
			link.l1 = "А это будет зависеть только от вас, минхер Томас. Если вы выполните мою маленькую просьбу, то я позволю всем, кто сложил оружие, взять своих раненых и отправиться отсюда на корабле или кораблях, которые мы найдем в доках, на Кюрасао к минхеру Стайвесанту. В противном случае вас ждут трюмы моих кораблей и казематы на Сент-Кристофере. Также, какого-нибудь важного голландского чиновника придется показательно вздернуть на рее, чтобы отвадить у Стайвесанта желание нападать на наши колонии...";
			link.l1.go = "tomas_3";
		break;
		
		case "tomas_3":
			dialog.text = "(заикаясь) Ка... какое... о как...ой просьбе ре... речь?";
			link.l1 = "В глубине острова находится яблоко раздора - соляной рудник. Мне известно, что там находятся не только шахтеры и рабы, но также до зубов вооруженные голландские солдаты. Думаю, из гвардии Компании, не так ли, минхер? Я должен либо предложить им сдаться, либо применить силу в случае отказа. Мне нужен проводник, который покажет дорогу к руднику. Найдите мне такого проводника.";
			link.l1.go = "tomas_4";
		break;
		
		case "tomas_4":
			dialog.text = "Сол... соляной руд... ник?";
			link.l1 = "Да-да. Не бойтесь, минхер Томас, если охрана рудника проявит благоразумие и сложит оружие, я предоставлю им возможность покинуть остров. Мне не нужно лишнего кровопролития. И не терзайтесь муками совести: остров Синт-Маартен весьма невелик, я и без вашей помощи найду рудник, просто не хочу терять время, шатаясь по зарослям и болотам. Так что эта сделка выгоднее вам, нежели мне.";
			link.l1.go = "tomas_5";
		break;
		
		case "tomas_5":
			dialog.text = "Хо... хорошо, я расскажу вам, как пройти на рудник, но вы да... дадите слово, что все... все мы покинем остров!..";
			link.l1 = "Даю вам слово офицера и дворянина.";
			link.l1.go = "tomas_6";
		break;
		
		case "tomas_6":
			dialog.text = "В бухте Гранд Кейс у... у дальнего ее края, у воды, есть... есть камни. Та... там, за ними, вдоль береговой линии, есть проход по воде, там... там неглубоко, по пояс или меньше. Надо обогнуть скалу и за ней будет большой пляж, к... к которому нельзя причалить на корабле из-за рифов. С этого пляжа есть тропа прямо...на... на рудник.";
			link.l1 = "Отлично. Я отправляюсь. А вы, минхер, до нашего возвращения, останетесь здесь под охраной моих солдат.";
			link.l1.go = "tomas_7";
		break;
		
		case "tomas_7":
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			LAi_SetActorType(npchar);
			pchar.quest.Patria_BastionGate.win_condition.l1 = "location";
			pchar.quest.Patria_BastionGate.win_condition.l1.location = "Shore40";
			pchar.quest.Patria_BastionGate.function = "Patria_BastionShore";
			AfterTownBattle();
			AddQuestRecord("Patria", "50_1");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

