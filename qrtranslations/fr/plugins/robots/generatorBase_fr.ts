<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="fr_FR">
<context>
    <name>QObject</name>
    <message>
        <location filename="../../../../plugins/robots/generators/generatorBase/src/converters/reservedVariablesConverter.cpp" line="+64"/>
        <source>Device on port %1 is not configured. Please select it on the &quot;Configure devices&quot; panel on the right-hand side.</source>
        <translation>Le capteur sur le port %1 n&apos;est pas configuré. S&apos;il vous plait, sélectionné son type sur le panel &quot;Configuration des capteurs&quot; sur votre droite.</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>/* ERROR: SELECT DEVICE TYPE */</source>
        <translation>/* ERREUR SELECTIONNEZ LE TYPE DU CAPTEUR */</translation>
    </message>
    <message>
        <location filename="../../../../plugins/robots/generators/generatorBase/src/masterGeneratorBase.cpp" line="+79"/>
        <source>There is no opened diagram</source>
        <translation>Il n&apos;y a pas de diagramme d&apos;ouvert</translation>
    </message>
    <message>
        <location filename="../../../../plugins/robots/generators/generatorBase/src/parts/subprograms.cpp" line="+83"/>
        <source>Graphical diagram instance not found</source>
        <translation>L&apos;instance graphique du diagramme n&apos;est pas trouvé</translation>
    </message>
    <message>
        <location line="+125"/>
        <source>Please enter valid c-style name for subprogram &quot;</source>
        <translation>Entrez un identificateur valide de style C pour le sous-programme &quot;</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Subprograms should have unique names, please rename</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Duplicate identifier: </source>
        <translation type="vanished">Cet identificateur est deja utilisé:</translation>
    </message>
    <message>
        <location filename="../../../../plugins/robots/generators/generatorBase/src/primaryControlFlowValidator.cpp" line="+44"/>
        <source>There is nothing to generate, diagram doesn&apos;t have Initial Node</source>
        <translation>Impossible de générer le code car le diagramme ne contient pas de nœud initial</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>Initial node must not have incoming links</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location line="+34"/>
        <source>This element must have exactly ONE outgoing link</source>
        <translation>Cet élément doit avoir exactement un lien de sortie</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>Final node must not have outgoing links</source>
        <translation>Le nœud terminal ne doit pas avoir de liens sortants</translation>
    </message>
    <message>
        <location line="+8"/>
        <source>If block must have exactly TWO outgoing links</source>
        <translation>Le bloc conditionnel doit avoir exactement deux liens sortants</translation>
    </message>
    <message>
        <location line="+15"/>
        <source>Two outgoing links marked with &apos;true&apos; found</source>
        <translation>Les deux liens sortants sont marqués comme &apos;vrai&apos;</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>Two outgoing links marked with &apos;false&apos; found</source>
        <translation>Les deux liens sortants sont marqués comme &apos;faux&apos;</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>There must be at least one link with &quot;true&quot; or &quot;false&quot; marker on it</source>
        <translation>Il doit exister au moins un lien marqué comme &quot;vrai&quot; ou &quot;faux&quot;</translation>
    </message>
    <message>
        <location line="+29"/>
        <source>Loop block must have exactly TWO outgoing links</source>
        <translation>Le bloc de boucle doit avoir exactement deux liens sortants</translation>
    </message>
    <message>
        <location line="+14"/>
        <source>Two outgoing links marked with &quot;body&quot; found</source>
        <translation>Deux liens sortants marqués sont marqués comme &quot;corps de boucle&quot;</translation>
    </message>
    <message>
        <location line="+8"/>
        <source>There must be a link with &quot;body&quot; marker on it</source>
        <translation>Le nœud de boucle doit avoir un lien sortant marqué comme &quot;corps de boucle&quot;</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>Outgoing links from loop block must be connected to different blocks</source>
        <translation>Les liens sortants du bloc boucle doivent être raccordé aux deux blocs différents</translation>
    </message>
    <message>
        <location line="+18"/>
        <source>There must be at list TWO links outgoing from switch block</source>
        <translation>Le bloc de choix multiple doit avoir au moins deux liens sortants</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>There must be exactly one link without marker on it (default branch)</source>
        <translation>Il doit exister exactement un lien sans un marquer associé (branche par defaut)</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Duplicate case branch: &apos;%1&apos;</source>
        <translation>Des doublons ont étés détéctés pour la branche &apos;%1&apos;</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>There must be a link without marker on it (default branch)</source>
        <translation>Il doit exister un lien sans un marquer associé (branche par defaut)</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Unknown block type</source>
        <translation>Un bloc inconnu</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Fork block must have at least TWO outgoing links</source>
        <translation>Un bloc de parallelisation de taches doit posseder au moins deux liens sortants</translation>
    </message>
    <message>
        <location line="+26"/>
        <source>Outgoing link is not connected</source>
        <translation>Le lien sortant n&apos;est pas raccordé</translation>
    </message>
</context>
<context>
    <name>generatorBase::MasterGeneratorBase</name>
    <message>
        <location filename="../../../../plugins/robots/generators/generatorBase/src/masterGeneratorBase.cpp" line="+40"/>
        <source>This diagram cannot be generated into the structured code. Generating it into the code with &apos;goto&apos; statements.</source>
        <translation>Ce diagramme ne peut pas être transformé en code structuré. Le code contenant &apos;goto&apos; sera généré.</translation>
    </message>
    <message>
        <location line="+15"/>
        <source>This diagram cannot be even generated into the code with &apos;goto&apos;statements. Please contact the developers.</source>
        <translation>Ce diagramme ne peut pas être transformé même en code avec des expressions &apos;goto&apos;. S&apos;il vous plait, contactez les developpeurs.</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>This diagram cannot be generated into the structured code.</source>
        <translation>Ce diagramme ne peut pas être transformé en code structuré.</translation>
    </message>
</context>
</TS>
