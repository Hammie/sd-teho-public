// Жаклин Тьюрам - торговый капитан
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Я не желаю с тобой общаться. Ты нападаешь без причины на мирных граждан, провоцируешь их на драку. Уходи прочь!";
				link.l1 = "Гм...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Здравствуйте, месье. Вы ведь недавно у нас, я прав?";
				link.l1 = TimeGreeting()+". Да, я, наверное, самый 'новый' житель Острова. Мое имя - "+GetFullName(pchar)+". А вы?..";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetFullName(pchar)+"! Что вас привело ко мне?";
				link.l1 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Я хочу задать вам пару вопросов об острове.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Да просто решил узнать как у вас дела. Еще увидимся!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Жаклин Тьюрам. Еще два года назад я был вполне преуспевающим торговцем, владельцем и капитаном собственного флейта, а теперь - увы! Я беден, как церковная крыса, и живу без малейшей надежды на то, что ситуация как-то изменится\nКому-то на Острове везет - находят на внешнем кольце корабли с богатым грузом, бочки с золотыми слитками, мешочки с драгоценными камнями, я же ничего, кроме одного сундучка с дублонами да всякой мелочевки не обнаружил\nХорошо, хоть и это есть, а то купить еды было бы не за что... Рад знакомству, сударь, если что - подходите, поболтаем.";
			link.l1 = "Мне тоже приятно с вами познакомиться, Жаклин. Еще увидимся!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Я хочу задать вам пару вопросов об острове.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Внимательно вас слушаю.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Какими судьбами вы здесь, на Острове?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Чем вы занимаетесь на Острове?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Скажите, вот я вижу, что на Острове есть и девушки, и женщины...";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Вы бы хотели вернуться назад, в большой мир?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извините...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Вы хотите узнать эту историю? Что же, я расскажу вам. Как вы уже знаете, я был торговым капитаном. В один злосчастный день я вышел на своем верном флейте из порта Белиза и направился на Тортугу. В трюмах у меня было полно черного дерева и какао - я вложил в этот груз все свои сбережения\nНа Тортуге я заключил очень выгодное соглашение с одним человеком, он хотел приобрести дерево и какао по очень привлекательной цене. Я зарабатывал на этой сделке целую кучу денег. Все шло как нельзя хорошо - погода была чудесной, корабль скользил по волнам, словно ласточка. Казалось, ничто не предвещало беды\nЯ огибал Кубу с севера, держась подальше от испанских берегов, и тут как гром среди ясного неба на нас напал пиратский галеон. И откуда он только взялся в тех водах - там же кишмя кишат испанские военные патрули? Я попытался уйти от него, но его корабль был быстрее, это был на удивление быстрый галеон\nПираты нагнали нас и пошли в атаку. Их кулеврины были заряжены картечью - первым же залпом они нанесли тяжелый урон моей команде, полностью деморализовав ее. Я хотел дать бой, но матросы и офицеры заставили меня поднять белый флаг. Мы сдались без боя\nПираты без долгих разговоров перегрузили содержимое нашего трюма на свой корабль, выбросили за борт наши пушки и стали поднимать паруса. Я думал, что на этом все и закончится. Конечно, потеря груза была тяжким ударом, но имея корабль я смог бы зарабатывать на фрахтах, и, в итоге, снова встать на ноги\nОднако все повернулось иначе. Подлецы отошли на небольшое расстояние и открыли по моему беззащитному флейту огонь на потопление. Мы были отличной мишенью. Борта превратились в щепки, одна мачта рухнула, в пробоины ниже ватерлинии хлынула вода и корабль стал стремительно погружаться под воду\nЯ до сих пор слышу хохот этих нелюдей... Затем галеон ушел, а мы барахтались в воде, цепляясь за обломки. А потом подул свежий ветер, поднялись волны, и больше я никогда не видел ни одного человека из своей команды. Я успел привязать себя веревками к толстому обломку мачты, и остался на плаву\nКак меня мотало целый день по морю, как меня чуть не сожрала акула - я избавлю вас от описания этих жутких подробностей. Скажу лишь одно: через промежуток времени, показавшийся мне вечностью, меня вынесло течением к Острову. Так я и спасся.";
			link.l1 = "Да, действительно грустная история...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Тем же, что и все остальные - просто живу. Разыскиваю ценные вещицы на внешнем кольце кораблей и обмениваю их на еду. Лелею надежду когда-нибудь найти сундук с сокровищами какого-нибудь индийского набоба... Ну, или хотя бы просто галеон с испанским золотом, хе-хе. Ладно, не обращайте внимания, это я так\nМечтаю поесть чего-нибудь кроме солонины или рыбы. Эх, вот раньше был тут у нас человек, который охотился на гигантских крабов. У них такое вкусное мясо, особенно на клешнях. Я покупал его по пять дублонов за одну клешню, а потом объедался несколько дней\nЖаль, что этот охотник погиб... хотя это и неудивительно - охотиться на таких тварей весьма опасное занятие.";
			link.l1 = "Ясно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Я понял, на что вы намекаете. Да, любовные истории и интрижки имеют место быть на Острове. А как же без этого? Мужчина создан для женщины, женщина - для мужчины. Это нормально. Можете попытать счастья с Джиллиан, или с Таннеке. Они молодые, симпатичные и благосклонно относятся к ухаживаниям\nЯ вот, например, нашел себе подругу - Наталию. Это официантка в таверне Санчо Карпентеро. Прекрасная девушка, скажу я вам. Наверное, только благодаря ей я не лишился рассудка в первые месяцы после попадания на Остров. Она очень помогла мне, и вот теперь мы вместе.";
			link.l1 = "Хм... Приму к сведению!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Хороший вопрос. С одной стороны - конечно, да. Но если немного подумать, то... я ведь разорен. Сбережения мои были вложены в товар, захваченный пиратами, корабль потоплен - у меня фактически нет средств к существованию. Мне ничего более не останется, как наняться на службу в Голландскую торговую Компанию клерком, и то, если возьмут\nЕсли бы у меня были деньги, достаточные для покупки и снаряжения хотя бы шхуны - тогда и разговор был бы другой. А так... уж лучше мне сидеть тут, на Острове. По крайней мере, здесь не нужно вкалывать от зари до зари за корку черствого хлеба.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Что ты там копаешься, а? Да ты вор!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой!", "По сундукам шарить вздумал?! Тебе это даром не пройдет!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ах, вот, значит, как?! По сундукам шарить вздумал?! Тебе это даром не пройдет!";
			link.l1 = "Вот дура!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Слушай, ты бы убрал оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как д'Артаньян, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это серьезному мужчине...");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
				link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Острожней на поворотах, приятель, когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда мужчины ходят передо мной с оружием на изготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял.", "Убираю.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}